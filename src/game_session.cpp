#include "game_session.hpp"
#include "word_database.hpp"
#include <godot_cpp/variant/utility_functions.hpp>

namespace FiveLetters {

    void GameSession::_bind_methods() {
        using namespace godot;

        ClassDB::bind_method(D_METHOD("get_max_attempts"), &GameSession::get_max_attempts);
        ClassDB::bind_method(D_METHOD("set_max_attempts", "p_value"), &GameSession::set_max_attempts);
        ClassDB::bind_method(D_METHOD("set_path", "p_value"), &GameSession::set_path);
        ClassDB::bind_method(D_METHOD("get_path"), &GameSession::get_path);
        ClassDB::bind_method(D_METHOD("start_game"), &GameSession::start_game);

        ClassDB::add_property("GameSession", PropertyInfo(Variant::STRING, "path"), "set_path", "get_path");
        ClassDB::add_property("GameSession", PropertyInfo(Variant::INT, "max_attempts"), "set_max_attempts", "get_max_attempts");
    }

    GameSession::GameSession() {}
    GameSession::~GameSession() {}

    void GameSession::_ready() {
        start_game();
    }

    void GameSession::set_path(godot::String _path) {
        path = _path;
    }

    void GameSession::start_game() {
        godot::UtilityFunctions::print("Game session started with ", max_attempts, " attempts.");
        godot::UtilityFunctions::randomize();
        word_db.instantiate();
        if (path.is_empty()) { return; }
        word_db->load_from_file(path);
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

} // namespace FiveLetters