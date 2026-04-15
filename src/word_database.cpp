#include "word_database.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <unordered_set>

namespace FiveLetters {

    void WordDatabase::_bind_methods() {
        using namespace godot;

        ClassDB::bind_method(D_METHOD("load_from_file", "p_path"), &WordDatabase::load_from_file);
        ClassDB::bind_method(D_METHOD("is_word_valid", "p_word"), &WordDatabase::is_word_valid);
        ClassDB::bind_method(D_METHOD("get_random_word"), &WordDatabase::get_random_word);
    }

    WordDatabase::WordDatabase() {}
    WordDatabase::~WordDatabase() {}

    bool WordDatabase::load_from_file(const godot::String& p_path) {
        godot::Ref<godot::FileAccess> file = godot::FileAccess::open(p_path, godot::FileAccess::READ);
        if (!file.is_valid()) return false;

        while (file->eof_reached() != true) {
            godot::String line = file->get_line();
            line = line.strip_edges();
            if (!line.is_empty()) words.insert(line);
        }
        return true;
    }

    bool WordDatabase::is_word_valid(const godot::String& p_word) const {
        return words.find(p_word) != words.end();
    }

    godot::String WordDatabase::get_random_word() const {
        if (words.empty()) return "ERROR";
        auto it = words.begin();
        it = std::next(it, godot::UtilityFunctions::randi() % words.size());
        return *it;
    }

} // namespace FiveLetters