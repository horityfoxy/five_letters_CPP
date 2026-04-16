#include "word_validator.hpp"
#include <unordered_map>

namespace FiveLetters {
    void ValidateGuess::_bind_methods() {
        using namespace godot;

        ClassDB::bind_method(D_METHOD("get_letters_status", "f_value", "s_value"), &ValidateGuess::get_letters_status);
    }

    ValidateGuess::ValidateGuess() {}
    ValidateGuess::~ValidateGuess() {}
    
    godot::PackedInt32Array ValidateGuess::get_letters_status(const godot::String& guess_word, const godot::String& correct_word) const {
        if (guess_word.length() != correct_word.length()) return godot::PackedInt32Array();
        godot::PackedInt32Array result;
        result.resize(guess_word.length());

        std::unordered_map<char32_t, int> letter_counts;
        for (int i = 0; i < correct_word.length(); ++i) {
            letter_counts[correct_word[i]]++;
        }

        for (int i = 0; i < correct_word.length(); ++i) {

            result[i] = ABSENT;

            if (guess_word[i] == correct_word[i]) {
                result[i] = CORRECT;
                letter_counts[correct_word[i]]--;
            }
        }
        for (int i = 0; i < correct_word.length(); ++i) {
            if (result[i] != ABSENT) continue;
            char32_t current_char = guess_word[i];

            if (letter_counts[current_char] > 0) {
                result[i] = MISPLACED;
                letter_counts[current_char]--;
            }
        }
        return result;
    }
}