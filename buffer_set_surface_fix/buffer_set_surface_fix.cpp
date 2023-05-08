/// @author YellowAfterlife

#include "stdafx.h"
enum RValueType : int32_t {
	Real = 0,
	Int32 = 7,
	Int64 = 10,
	Bool = 13,
};
struct RValue {
	union {
		int32_t v32;
		int64_t v64;
		double real;
		void* ptr;
	};
	int32_t flags = 0;
	RValueType type = Real;
	RValue() { real = 0; }
	RValue(double val) { real = val; }
};
typedef void(*GMLFunc)(RValue& result, void* self, void* other, int argc, RValue* args);
struct GMLClosure {
	int __mysteries[26];
	GMLFunc call;
};

static int sprite_id;
static GMLClosure* draw_sprite_stretched_ext;
struct BGRA {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t alpha;
	inline uint32_t asU32() {
		return *(uint32_t*)this;
	}
};

dllx void buffer_set_surface_fallback_init(void* ptr, double spr) {
	draw_sprite_stretched_ext = (GMLClosure*)ptr;
	sprite_id = (int)spr;
}
dllx void buffer_set_surface_fallback(uint8_t* _data, double _width, double _height, double _offset) {
	if (draw_sprite_stretched_ext == nullptr) return;
	static_assert(sizeof(BGRA) == 4);
	_data += (ptrdiff_t)_offset;
	auto bgra = (BGRA*)_data;
	auto width = (int)_width;
	auto height = (int)_height;
	RValue result;
	RValue args[] = { (double)sprite_id, 0, 0, 0, 1, 1, -1, 1 };
	auto func = draw_sprite_stretched_ext->call;
	for (int y = 0; y < height; y++) {
		auto row = bgra + width * y;
		int x = 0;
		args[3].real = y;
		while (x < width) {
			auto col = row[x++];
			if (col.alpha == 0) continue;
			std::swap(col.red, col.blue);
			args[2].real = x - 1;
			auto count = 1;
			while (x < width) {
				if (row[x].asU32() == col.asU32()) {
					count += 1;
					x += 1;
				} else break;
			}
			args[4].real = count;
			args[7].real = (double)col.alpha / 255.;
			col.alpha = 0;
			args[6].real = col.asU32();
			func(result, 0, 0, 8, args);
		}
	}
}

static inline void init() {
	sprite_id = -1;
	draw_sprite_stretched_ext = nullptr;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) init();
	return TRUE;
}
