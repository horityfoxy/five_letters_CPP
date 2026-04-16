#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>

namespace FiveLetters {
    class ValidateGuess : public godot::RefCounted {
        GDCLASS(ValidateGuess, godot::RefCounted)

    protected:
        static void _bind_methods();

    public:
        enum letter_status { CORRECT = 0, MISPLACED = 1, ABSENT = 2 };
        ValidateGuess();
        ~ValidateGuess();

        godot::PackedInt32Array get_letters_status(const godot::String& guess_word, const godot::String& correct_word) const;
    };

} // namespace FiveLetters