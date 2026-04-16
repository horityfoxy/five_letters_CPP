#include "game_session.hpp"
#include "word_database.hpp"
#include "word_validator.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

namespace FiveLetters {

    void GameSession::_bind_methods() {
        using namespace godot;

        ClassDB::bind_method(D_METHOD("get_max_attempts"), &GameSession::get_max_attempts);
        ClassDB::bind_method(D_METHOD("set_max_attempts", "p_value"), &GameSession::set_max_attempts);
        ClassDB::bind_method(D_METHOD("process_guess", "p_value"), &GameSession::process_guess);
        ClassDB::bind_method(D_METHOD("set_path", "p_value"), &GameSession::set_path);
        ClassDB::bind_method(D_METHOD("get_path"), &GameSession::get_path);
        ClassDB::bind_method(D_METHOD("start_game"), &GameSession::start_game);

        ClassDB::add_property("GameSession", PropertyInfo(Variant::STRING, "path"), "set_path", "get_path");
        ClassDB::add_property("GameSession", PropertyInfo(Variant::INT, "max_attempts"), "set_max_attempts", "get_max_attempts");
        ClassDB::add_signal("GameSession", MethodInfo("guess_processed", PropertyInfo(Variant::PACKED_INT32_ARRAY, "statuses")));
    }

    GameSession::GameSession() {}
    GameSession::~GameSession() {}

    void GameSession::_ready() {
        godot::UtilityFunctions::randomize();
        word_db.instantiate();
        word_validator.instantiate();
        if (path.is_empty()) { return; }
        word_db->load_from_file(path);
        start_game();
    }

    void GameSession::set_path(godot::String _path) {
        path = _path;
    }

    void GameSession::start_game() {
        godot::UtilityFunctions::print("Game session started with ", max_attempts, " attempts.");
        secret_word = word_db->get_random_word();
    }

    int GameSession::get_max_attempts() const {
        return max_attempts;
    }

    godot::String GameSession::get_path() const {
        return path;
    }

    void GameSession::set_max_attempts(int p_value) {
        max_attempts = p_value;
    }

    godot::PackedInt32Array GameSession::process_guess(const godot::String& player_guess_word) {
        if (max_attempts > 0) {
            godot::PackedInt32Array result = word_validator->get_letters_status(player_guess_word, secret_word);
            if (!result.is_empty()) {
                max_attempts--;
                emit_signal("guess_processed", result);
            }
            return result;
        }
        return godot::PackedInt32Array();
    }

} // namespace FiveLetters