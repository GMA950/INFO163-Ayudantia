with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;
with Ada.Numerics.Float_Random;
with Ada.Real_Time;

with Semaforos;

procedure canibales is

    subtype rangerand is Integer range 1..9;
    package Random_Gen is new Ada.Numerics.Discrete_Random(rangerand);

    use Random_Gen;

    G: Generator;


    use Ada.Real_Time;
    periodo: constant Time_Span := Milliseconds(200);
    Next_time: Time := clock;
    c: integer := 200;
    Num_Canibales : constant :=20;
    Num_Comidas : constant := 10;

    type Num_Canibal is range 1 .. Num_Canibales;
    type Num_Comida is range 1 .. Num_Comidas;

    package CanibNum is new Ada.Text_IO.Integer_IO (Num_Canibal);
    use CanibNum;
    package ComidaNum is new Ada.Text_IO.Integer_IO (Num_Comida);
    use ComidaNum;

    package Semaforos_Init is new
        Semaforos (Valorinicial => 1);
    use Semaforos_Init;

    Semaforos_Comida : array (Num_Comida) of TSemaforo;

    task type Canibal is
        entry Comenzar (Tu_Num : in Num_Canibal);
    end Canibal;

    Lista_Canibales : array (Num_Canibal) of Canibal;

    task body Canibal is 
        Mi_Num: Num_Canibal;

        procedure Pon_Num is
        begin
            Put ("Canibal n° "); Put (Mi_Num); Put (": ");
        end Pon_Num;

        Tiempo_Comiendo: constant Duration:= 1.0;
        Comio_Apurado: constant Duration:= 2.0;
        Factor_Tiempo: constant Duration := 1.0;
        Azar_Gen: Ada.Numerics.Float_Random.Generator;

        Actual, act: Num_Comida;
        var: Integer;
        
begin

    Ada.Numerics.Float_Random.Reset(Azar_Gen);

    accept Comenzar (Tu_Num : in Num_Canibal) do
        Mi_Num := Tu_Num;
    end Comenzar;

    Pon_Num;
    Put_Line ("Comienza el festin");
    var:= Random(G);
    for i in 1..var loop
        Actual := Actual + 1;
    end loop;
    act := Actual;

    loop

        delay until Next_time;
        Put_Line("Canibal espera a sacar comida");
        Wait(Semaforos_Comida(Actual));

        Pon_Num;
        Put (" Comiendo el plato ");
        Put (Actual);
        New_Line;

        delay Tiempo_Comiendo;
        Put("Chef reponiendo comida en plato ");
        Signal (Semaforos_Comida(Actual));

        
        Put(Actual);
        New_Line;

        while act = Actual loop
            var:= Random(G);
            for i in 1..var loop
                Actual := Actual + 1;
            end loop;
        end loop;
    

    end loop;
end Canibal;

begin

    for I in Lista_Canibales'Range loop
        Lista_Canibales (I).Comenzar (Tu_Num => I);
    end loop;
    Put_Line("Fin");
end canibales;

        


