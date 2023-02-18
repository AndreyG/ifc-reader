export module M;

export
{
    class A {};

    template<typename... Ts>
    class B : Ts... {};

    template<typename... Us>
    class C : A, B<Us>..., B<Us...> {};
}
