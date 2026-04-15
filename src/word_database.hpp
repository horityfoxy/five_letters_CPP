#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/string.hpp>
#include <unordered_set>

namespace FiveLetters {

    struct GodotStringHash {
        std::size_t operator()(const godot::String& k) const {
            return static_cast<std::size_t>(k.hash());
        }
    };

    class WordDatabase : public godot::RefCounted {
        GDCLASS(WordDatabase, godot::RefCounted)

    private:
        std::unordered_set<godot::String, GodotStringHash> words;

    protected:
        static void _bind_methods();

    public:
        WordDatabase();
        ~WordDatabase();

        bool load_from_file(const godot::String& p_path);
        bool is_word_valid(const godot::String& p_word) const;
        godot::String get_random_word() const;
    };

} // namespace FiveLetters