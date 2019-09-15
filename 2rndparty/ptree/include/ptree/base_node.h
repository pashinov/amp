#ifndef BASE_NODE_H
#define BASE_NODE_H

// internal
#include "traits.h"

// std
#include <optional>

namespace ptree
{
    template <typename Traits>
    class base_node
    {
    public:
        ~base_node();

        bool set_value(const typename Traits::value_t& value);
        
        typename Traits::node_ptr add_child(const typename Traits::key_t& key);
        typename Traits::node_ptr add_child(const typename Traits::key_t& key, const typename Traits::value_t& value);

        [[nodiscard]] bool empty() const;
        [[nodiscard]] bool has_children() const;
        [[nodiscard]] bool has_value() const;

        const typename Traits::key_t& key() const;

        typename Traits::node_ptr parent() const;

        const typename Traits::value_t& value() const;
        const typename Traits::value_t& value(const typename Traits::value_t& default_value) const;

        const typename Traits::children_t& children() const;
        const typename Traits::children_t& children(const typename Traits::children_t& default_value) const;

        typename Traits::node_ptr child(const typename Traits::key_t& key);

        bool exist(const typename Traits::node_ptr child) const;
        bool exist(const typename Traits::key_t& child) const;

        void value_reset();
        void clear();
        void erase(const typename Traits::key_t& key);

        const typename Traits::value_changed_t& value_changed() const;

        static typename Traits::node_ptr root();

    protected:
        explicit base_node(const typename Traits::key_t& key, typename Traits::node_ptr parent = nullptr);

    private:
        enum class holds_value_t : std::uint8_t { empty, value, child };

        typename Traits::node_ptr create_child(const typename Traits::key_t& key);
        typename Traits::node_ptr create_child(const typename Traits::key_t& key, const typename Traits::value_t& value);

    private:
        typename Traits::key_t key_                    { typename Traits::key_t() };
        std::optional<typename Traits::value_t> value_ { std::nullopt };
        typename Traits::node_ptr parent_              { nullptr };
        typename Traits::children_t children_          { typename Traits::children_t() };
        holds_value_t holds_value_                     { holds_value_t::empty };

        typename Traits::value_changed_t value_changed_;
    };

} //namespace

#endif // BASE_NODE_H

#include "base_node.hpp"