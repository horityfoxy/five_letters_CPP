#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>

namespace FiveLetters {
    class WordDatabase;
    class ValidateGuess;

    class GameSession : public godot::Node {
        GDCLASS(GameSession, godot::Node)

    private:
        int max_attempts = 6; 
        godot::String secret_word = "";
        godot::String path = "";
        godot::Ref<WordDatabase> word_db;
        godot::Ref<ValidateGuess> word_validator;
    protected:
        static void _bind_methods();
    public:
        GameSession();
        ~GameSession();

        void _ready() override;

        void start_game();
        void set_path(godot::String _path);
        int get_max_attempts() const;
        godot::String get_path() const;
        godot::PackedInt32Array process_guess(const godot::String& player_guess_word);
        void set_max_attempts(int p_value);
    };

} // namespace FiveLetters