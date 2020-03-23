with Ada.Text_IO, Ada.Numerics.Discrete_Random, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure fumador is

    subtype rangerand is Integer range 1..20;
    package RandomGen is new Ada.Numerics.Discrete_Random(rangerand);
    use RandomGen;

    Gen : Generator;

    task proveedor is

        entry CITA_TABACO;
        entry CITA_PAPEL;
        entry CITA_FUEGO;
        entry CITA_REPONER;

    end proveedor;

    task body proveedor is
        fuego, papel, tabaco: integer;

    begin
        RandomGen.Reset(Gen);

        fuego:= Random(Gen);
        tabaco:= Random(Gen);
        papel:= Random(Gen);

        Put_line("fuego disponible = " & Integer'Image(fuego));
        Put_line("Tabaco disponible = " & Integer'Image(tabaco));
        Put_line("Papel disponible = " & Integer'Image(papel));

        loop
            select
                when (fuego > 0 and papel > 0) =>
                    accept CITA_TABACO do 
                        fuego:= fuego - 1;
                        papel:= papel - 1;
                        Put_Line("Fumador con tabaco pide papel y fuego");
                    end CITA_TABACO;
                or when (fuego > 0 and tabaco > 0) =>
                    accept CITA_PAPEL do
                        fuego:= fuego - 1;
                        tabaco:= tabaco - 1;
                        Put_Line("Fumador con papel pide fuego  y tabaco");
                    end CITA_PAPEL;
                or when (papel > 0 and tabaco > 0) =>
                    accept CITA_FUEGO do
                        papel:= papel - 1;
                        tabaco:= tabaco - 1;
                        Put_Line("Fumador con fuego pide papel y tabaco");
                    end CITA_FUEGO;
                or when ((papel = 0 and tabaco = 0) or (papel = 0 and fuego = 0) or (fuego = 0 and tabaco = 0)) =>
                    accept CITA_REPONER do
                        papel:= 10;
                        tabaco:= 10;
                        fuego:= 10;
                        Put_Line("Proveedor repone recursos");
                    end CITA_REPONER;
            end select;

            Put_Line("Fuego restante: " & Integer'Image(fuego));
            Put_Line("Tabaco restante: " & Integer'Image(tabaco));
            Put_Line("Papel restante: " & Integer'Image(papel));
        end loop;
    end proveedor;

    task FumadorConTabaco;
    task FumadorConPapel;
    task FumadorConFuego;
    task ReponerRecursos;

    task body FumadorConTabaco is
    begin
        loop
            proveedor.CITA_TABACO;
        end loop;
    end FumadorConTabaco;

    task body FumadorConPapel is
    begin
        loop
            proveedor.CITA_PAPEL;
        end loop;
    end FumadorConPapel;

    task body FumadorConFuego is
    begin
        loop
            proveedor.CITA_FUEGO;
        end loop;
    end FumadorConFuego;

    task body ReponerRecursos is
    begin
        loop
            proveedor.CITA_REPONER;
        end loop;
    end ReponerRecursos;

begin
    null;
end fumador;

