#ifndef _HANDLEABLE_H
#define _HANDLEABLE_H

#include <vector>

// Abstract class for any object that can be "handleable"
// (ie. would need a function to run regularly in the loop)
class Handleable {
    public:
        /**
         * Adds this object to the handler's list of handleables
         */
        Handleable();

        /**
         * Removes this object from the handler's list of handleables
        */
        virtual ~Handleable();

        /**
         * Begin Handleable Object
         * */
        virtual void begin() = 0;

        /**
         * Run Handleable object every loop
         * */
        virtual void handle() = 0;

        /*
         * Calls begin on all handleable objects
        */
        static void beginAll();

        /*
         * Calls handle on all currently active handleable objects
        */
        static void handleAll();

	private:
		bool _isActive = true;

        class Handler {
            public:
                /**
                 * Gets the Singleton instance of this class
                 * 
                 * @return reference to handler instance
                 */
                static Handler &instance();
                
                /**
                 * Add a handleable object to list of handleables
                 * 
                 * @param *handleable object to add
                 * */
                void add(Handleable* handleable);

                /**
                 * Remove a handleable object from list of handleables
                 * 
                 * @param *handleable object to remove
                 * */
                void remove(Handleable* handleable);

                /**
                 * @brief Checks whether the handler contains handleable
                 * 
                 * @returns true if handler contains handleable
                 */
                bool contains(Handleable* handleable);

                /**
                 * Run the begin() function of all handleables
                 * */
                void begin();

                /**
                 * Run the handle() function of all handleables
                 * */
                void handle();
            
            private:
                static Handler* _instance;
                std::vector<Handleable*> _handleables;
        };
        
};

#endif
