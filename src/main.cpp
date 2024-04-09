#include "main.h"
#include "spritelib/sprites.h"



void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


void draw_character(int character_info[3]) {
    int character_eyes_north_south = character_info[0];
    int character_eyes_east_west = character_info[1];
    int character_emotion = character_info[2];
    // Draw character
    std::string character_path = "/usd/char-" + std::to_string(character_eyes_north_south) +"-"+ std::to_string(character_eyes_east_west) +"-"+ std::to_string(character_emotion) + ".sprite";
    SpriteEngine engine;
    Sprite character = loadSprite(character_path);
    engine.addSprite(&character, 0, 0);

    
    uint32_t *pixels = new uint32_t[480 * 240];
    lv_obj_t *canvas = nullptr;
    canvas = lv_canvas_create(lv_scr_act(), NULL);
    lv_color_t *framebuf = new lv_color_t[480 * 240];

    engine.renderSprites(pixels, 480, 240);
    for (int i = 0; i < 480 * 240; i++) {
        uint32_t pixel = pixels[i];
        framebuf[i].red = (pixel >> 16) & 0xFF;
        framebuf[i].green = (pixel >> 8) & 0xFF;
        framebuf[i].blue = pixel & 0xFF;
        framebuf[i].alpha = (pixel >> 24) & 0xFF;
    }
    lv_canvas_set_buffer(canvas, framebuf, 480, 240, LV_IMG_CF_TRUE_COLOR);

}


void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);


    // north = 1
    // neutral = 0
    // south = 2

    // east = 1
    // neutral = 0
    // west = 2

    // emotions
    // neutral = 0
    // happy = 1
    // sad = 2

    

    int character_appearance[3] = {0, 0, 0};


	while (true) {


        // Y axis
        // north
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            character_appearance[0] = 1;
        // south
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            character_appearance[0] = 2;
        // neutral
        } else {
            character_appearance[0] = 0;
        }
        // east
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            character_appearance[1] = 2;
        // west
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            character_appearance[1] = 1;
        // neutral
        } else {
            character_appearance[1] = 0;
        }

        // emotions

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            character_appearance[2] = 1;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            character_appearance[2] = 2;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            character_appearance[2] = 0;
        }



		pros::delay(20);
	}
}
