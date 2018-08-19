#ifndef OGRE_APPLICATION_H_
#define OGRE_APPLICATION_H_

#include <exception>
#include <string>

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

namespace ogre_application {


    /* A useful type to define */
    typedef std::vector<Ogre::String> Strings;

    /* Our exception type */
    class OgreAppException: public std::exception
    {
        private:
            std::string message_;
        public:
            OgreAppException(std::string message) : message_(message) {};
            virtual const char* what() const throw() { return message_.c_str(); };
    };

    /* An asteroid */
    struct Asteroid {
        Ogre::Vector3 pos; // Position
        Ogre::Quaternion ori; // Orientation
        Ogre::Quaternion am; // Angular momentum (use as velocity)
        Ogre::Vector3 drift; // Drift direction
    };

    /* Possible directions of the ship */
    enum Direction { Forward, Backward, Up, Down, Left, Right };

    /* Our Ogre application */
    class OgreApplication :
        public Ogre::FrameListener, // Derive from FrameListener to be able to have render event callbacks
        public Ogre::WindowEventListener // Derive from FrameListener to be able to have window event callbacks
        {

        public:
            OgreApplication(void);
            void Init(void); // Call Init() before running the main loop
            void CreateCube(void); // Create the geometry for a cube
            void CreateIcosahedron(void); // Create the geometry for an icosahedron
            void MainLoop(void); // Keep application active
			void CreateLaser(Ogre::String object_name);
			void CreateTargetCube(Ogre::String object_name);
			Ogre::SceneNode* OgreApplication::CreateEntity(Ogre::String entity_name, Ogre::String object_name, Ogre::String material_name);

            /* Camera demo */
            void CreateAsteroidField(int num_asteroids); // Create asteroid field
            void TransformAsteroidField(void); // Animate field 

        private:
            // Create root that allows us to access Ogre commands
            std::auto_ptr<Ogre::Root> ogre_root_;
            // Main Ogre window
            Ogre::RenderWindow* ogre_window_;

            /* Animation-related variables */
            bool animating_; // Whether animation is on or off
            bool space_down_; // Whether space key was pressed

            /* Camera demo variables */
            #define MAX_NUM_ASTEROIDS 1500 // Number of elements in the chain
            int num_asteroids_;
            Asteroid asteroid_[MAX_NUM_ASTEROIDS];
            Ogre::SceneNode* node_[MAX_NUM_ASTEROIDS];
            enum Direction last_dir_;

            // Input managers
            OIS::InputManager *input_manager_;
            OIS::Mouse *mouse_;
            OIS::Keyboard *keyboard_;

            /* Methods to initialize the application */
            void InitRootNode(void);
            void InitPlugins(void);
            void InitRenderSystem(void);
            void InitWindow(void);
            void InitViewport(void);
            void InitEvents(void);
            void InitOIS(void);
            void LoadMaterials(void);

            /* Methods to handle events */
            bool frameRenderingQueued(const Ogre::FrameEvent& fe);
            void windowResized(Ogre::RenderWindow* rw);

    }; // class OgreApplication

} // namespace ogre_application;

#endif // OGRE_APPLICATION_H_
