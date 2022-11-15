# Kompilator Lab 4 - JFTT 2019 / 2020

## Środowisko
Do napisania kompilatora zostały użyte następujące narzędzia:

- <b>Flex</b> w wersji 2.5.39,
- <b>Bison</b> w wersji 3.0.2,
- <b>Kompilator GNU g++-6</b> w wersji 6.5.0,
- <b>Linker GNU make</b> w wersji 3.81.

Kompilator został napisany i przetestowany pod systemem 'Ubuntu 14.04.6 LTS'. 
Wykorzystano język C++ w standardzie <b>C++17</b>.

## Instalacja i kompilacja

W celu poprawnej kompilacji (przy użyciu g++-6) należy zainstalować ten pakiet przy pomocy polecenia:
`sudo apt-get install g++-6`. Do kompilacji maszyny rejestrowej CLN są potrzebne pakiety, których ona wymaga:
`sudo apt-get install libcln6` oraz `sudo apt-get install libcln-dev`.

Aby zbudować kompilator należy użyć poleceń `make clean`
(usuwa niepotrzebne pliki po poprzedniej kompilacji), a następnie `make all`.

## Uruchamianie kompilatora

Aby uruchomić kompilator należy użyć polecenia `./kompilator fileIn fileOut`, gdzie:

- `fileIn` - nazwa pliku z programem wejściowym,
- `fileOut` - nazwa pliku z wynikowym kodem maszynowym.

Np.: `./kompilator test2.imp.txt a`

Po poprawnej kompilacji wynik zostaje zapisany do pliku 'fileOut', 
w razie wystąpienia błędów kompilacja jest przerywana i jest wyświetlany odpowiedni komunikat. 

## Interpreter
Skompilowane programy można uruchamiać na maszynie testowej oddanej do użytku studentów.
Programy wymagające obsługi bardzo dużych liczb (większych niż long long) powinno się uruchamiać na maszynie w wersji CLN (biblioteka obsługi dużych liczb).

## Specyfikacja języka
Język przeznaczony dla kompilatora jest opisany następującą gramatyką: 

```
    program      -> DECLARE declarations BEGIN commands END
				| BEGIN commands END

    declarations -> pidentifier
				| pidentifier(num:num)
    			| declarations , pidentifier;
                | declarations , pidentifier(num:num);
                | 

    commands     -> commands command
                | command

    command      -> identifier ASSIGN expression;
                | IF condition THEN commands ELSE commands ENDIF
                | IF condition THEN commands ENDIF
                | WHILE condition DO commands ENDWHILE
                | DO commands WHILE condition ENDDO
                | FOR pidentifier FROM value TO value DO commands ENDFOR
                | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR
                | READ identifier;
                | WRITE value;

    expression   -> value
                | value PLUS value
                | value MINUS value
                | value TIMES value
                | value DIV value
                | value MOD value

    condition    -> value = value
                | value != value
                | value < value
                | value > value
                | value <= value
                | value >= value

    value        -> num
                | identifier

    identifier   -> pidentifier
                | pidentifier(pidentifier)
                | pidentifier(num)
```

## Przykładowy program w tym języku:

```
[ Rozklad liczby 340282367713220089251654026161790386200 na czynniki pierwsze ]
[ Oczekiwany wynik:
  2^3
  3
  5^2
  7
  13
  41
  61
  641
  1321
  6700417
  613566757
  715827883
]
DECLARE
    a(0:3),
    n, m, reszta, potega, dzielnik
BEGIN
    a(0) ASSIGN 4294967297;
    a(1) ASSIGN 4294967298;
    a(2) ASSIGN 4294967299;
    a(3) ASSIGN 4294967300;

    n ASSIGN a(0) TIMES a(1);
    n ASSIGN n TIMES a(2);
    n ASSIGN n TIMES a(3);

    dzielnik ASSIGN 2;
    m ASSIGN dzielnik TIMES dzielnik;
    WHILE n GEQ m DO
        potega ASSIGN 0;
        reszta ASSIGN n MOD dzielnik;
        WHILE reszta EQ 0 DO
            n ASSIGN n DIV dzielnik;
            potega ASSIGN potega PLUS 1;
            reszta ASSIGN n MOD dzielnik;
        ENDWHILE
        IF potega GE 0 THEN [ czy znaleziono dzielnik ]
            WRITE dzielnik;
            WRITE potega;
        ELSE
            dzielnik ASSIGN dzielnik PLUS 1;
            m ASSIGN dzielnik TIMES dzielnik;
        ENDIF
    ENDWHILE
    IF n NEQ 1 THEN [ ostatni dzielnik ]
        WRITE n;
        WRITE 1;
    ENDIF
END
```




