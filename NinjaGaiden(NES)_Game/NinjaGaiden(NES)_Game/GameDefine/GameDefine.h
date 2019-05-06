#pragma once
namespace Define
{
#define WIN_NAME "NinjaGaiDen"
#define WIN_TITLE "NinjaGaiden"
#define FPS 60
#define KEYBOARD_BUFFERD_SIZE 1024
#define BUTTON_DOWN(obj, button) (obj.rgbButtons[button]&0x80)
#define CAMERA_SPEED 3
#define FrameWidth 32
#define FrameHeight 32
	const float PLAYER_MAX_JUMP_VELOCITY = 200.0f; //van toc nhay lon nhat
	const float PLAYER_MIN_JUMP_VELOCITY = -200.0f; //van toc nhay thap nhat
	const float PLAYER_MAX_RUNNING_SPEED = 150.0f; //toc do chay nhanh nhat cua player
	const float PLAYER_BOTTOM_RANGE_FALLING = 8.0f; // do dai va cham voi bottom neu nhu va cham bottom nho hon thi player se bi roi xuong
}