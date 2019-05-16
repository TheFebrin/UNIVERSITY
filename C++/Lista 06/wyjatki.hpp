namespace obliczenia
{
    class wyjatek_wymierny: public exception {};

    class dzielenie_przez_0: public wyjatek_wymierny{
        const char *what() const noexcept override{
            return "Nie można dzielić przez 0!\n";
        }
    };

    class przekroczenie_zakresu: public wyjatek_wymierny{
        const char *what() const noexcept override{
            return "Zakres int przekroczony!\n";
        }
    };
}
