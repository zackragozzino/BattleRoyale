#include "SkyWorld.hpp"

#include <iostream>

void SkyWorld::init(Loader &loader) {
    /* Camera */
    this->camera = new Camera();

    /* Main light source */
    this->light = new Light(glm::vec3(-500, 0, 500), glm::vec3(1.f));

    /* Skybox */
    std::string textureNames[6] = {
        "ame_nebula/purplenebula_ft.tga",
        "ame_nebula/purplenebula_bk.tga",
        "ame_nebula/purplenebula_up.tga",
        "ame_nebula/purplenebula_dn.tga",
        "ame_nebula/purplenebula_rt.tga",
        "ame_nebula/purplenebula_lf.tga",

    };
    //skybox = new Skybox(loader.loadCubeTexture(textureNames));

    /* Sun */
    sun = new Sun(this->light, glm::vec3(1.f), glm::vec3(1.f, 1.f, 0.f), 75, 150);

    /* Atmosphere */
    atmosphere = new Atmosphere(loader.loadObjMesh("geodesic_dome.obj"), 
                                loader.loadTexture("sky.png", Texture::WRAP_MODE::CLAMP), 
                                loader.loadTexture("glow.png", Texture::WRAP_MODE::CLAMP), 
                                1000.f);
}

void SkyWorld::prepareRenderer(MasterRenderer *mr) {
    mr->activateSkyboxShader(skybox);
    mr->activateAtmosphereShader(atmosphere);
    mr->activateSunShader(sun);
}

void SkyWorld::update(Context &ctx) {
    takeInput(ctx.mouse, ctx.keyboard);
    camera->update();

    if (skybox) {
        skybox->update(ctx.displayTime);
    }
    if (sun) {
        sun->update();
    }
}

void SkyWorld::takeInput(Mouse &mouse, Keyboard &keyboard) {
    if (mouse.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        camera->takeMouseInput(mouse.dx, mouse.dy);
    }
    else {
        camera->takeMouseInput(0.f, 0.f);
    }
    if (keyboard.isKeyPressed('w')) {
        camera->moveForward();
    }
    if (keyboard.isKeyPressed('a')) {
        camera->moveLeft();
    }
    if (keyboard.isKeyPressed('s')) {
        camera->moveBackward();
    }
    if (keyboard.isKeyPressed('d')) {
        camera->moveRight();
    }
    if (keyboard.isKeyPressed('e')) {
        camera->moveDown();
    }
    if (keyboard.isKeyPressed('r')) {
        camera->moveUp();
    }
    if (keyboard.isKeyPressed('z')) {
        light->position.y += 4.f;
    }
    if (keyboard.isKeyPressed('x')) {
        light->position.y -= 4.f;
    }
    if (keyboard.isKeyPressed('c')) {
        sun->updateInnerRadius(-5.f);
    }
    if (keyboard.isKeyPressed('v')) {
        sun->updateOuterRadius(-5.f);
    }
    if (keyboard.isKeyPressed('b')) {
        sun->updateInnerRadius(5.f);
    }
    if (keyboard.isKeyPressed('n')) {
        sun->updateOuterRadius(5.f);
    }
    if (keyboard.isKeyPressed('1')) {
        sun->innerColor += Toolbox::genRandomVec3(-1.f, 1.f);
    }
    if (keyboard.isKeyPressed('2')) {
        sun->outerColor += Toolbox::genRandomVec3(-1.f, 1.f);
    }
}

void SkyWorld::cleanUp() {

}