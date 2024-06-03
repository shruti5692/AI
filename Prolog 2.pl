% Define a dynamic predicate to store bike information.
:- dynamic bike/2.

% Predicate to input bike information.
input_bike_info(N) :-
    N > 0,
    write('Enter name of bike: '),
    read(BikeName),
    write('Enter price of bike: '),
    read(BikePrice),
    assertz(bike(BikeName, BikePrice)),
    NewN is N - 1,
    input_bike_info(NewN).
input_bike_info(0).

% Predicate to find the bike with the maximum price.
find_max_price_bike(MaxBike, MaxPrice) :-
    findall(Price, bike(_, Price), Prices),
    max_list(Prices, MaxPrice),
    bike(MaxBike, MaxPrice).

% Entry point for the program.
main :-
    write('Enter information for 5 bikes:\n'),
    input_bike_info(5),
    find_max_price_bike(MaxBike, MaxPrice),
    write('Bike with maximum price:\n'),
    format('Name: ~w\n', [MaxBike]), %
    format('Price: ~w\n', [MaxPrice]).


