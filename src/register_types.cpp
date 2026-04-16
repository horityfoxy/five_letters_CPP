#include "register_types.hpp"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_five_letters(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
    ClassDB::register_class<FiveLetters::GameSession>();
    ClassDB::register_class<FiveLetters::WordDatabase>();
    ClassDB::register_class<FiveLetters::ValidateGuess>();
}

void uninitialize_five_letters(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
    // отменить регистрацию
}

extern "C" {
    GDExtensionBool GDE_EXPORT five_letters_library_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization* r_initialization
    ) {
        GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
        init_obj.register_initializer(initialize_five_letters);
        init_obj.register_terminator(uninitialize_five_letters);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}