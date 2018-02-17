#pragma once
#ifndef _SOUND_SYSTEM_HPP_
#define _SOUND_SYSTEM_HPP_

// Set whether you have fmod library or not. Must be done manually!
#ifndef HAVE_FMOD_LIBRARY
#define HAVE_FMOD_LIBRARY false
#endif

#include "System.hpp"
#include "Component/SoundComponents/SoundComponent.hpp"
#include <string>
#include <vector>

#if HAVE_FMOD_LIBRARY 
#include "fmod.hpp"
#include "fmod_studio.hpp"
#endif

class SoundComponent;

class SoundSystem : public System {

    friend Scene;
    /* Attributes */
    public:
        std::vector<std::string> soundfiles = {
            "drill.wav",
            "doorbump.wav",
            "softbump.wav"
        };
    #if HAVE_FMOD_LIBRARY
        FMOD::System *m_system = NULL;
    #endif

    private:
        std::string SOUND_DIR;

    /* Constructor */
    public:
        SoundSystem(const std::vector<Component *> & components);

	private:
        /* Functions */
        void update(float dt);
        void setupSoundComponent(SoundComponent *c);
    #if HAVE_FMOD_LIBRARY
        FMOD::Sound* createSound(std::string soundfilename);
	    void playSound(int sid);
    #endif
};
#endif