#pragma once
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <unordered_set>

namespace FiveLetters {

    class WordDatabase : public godot::RefCounted {

    public:
        WordDatabase();
        ~WordDatabase();

        void load_from_file(godot::String p_path);
        bool is_word_valid(godot::String p_word);
        godot::String get_random_word() const;
    };

} // namespace FiveLetters