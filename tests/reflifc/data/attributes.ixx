export module attributes;

export {
    [[noreturn]] void a();

    [[nodiscard]] int b();

    [[maybe_unused]] void* c;

    struct [[deprecated]] d;

    class [[deprecated("use class 'f' instead")]] e {};
}
