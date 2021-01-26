# PokemonProject
This project helps the user find pokemon teams for any given input file of pokemon and their types. The user is allowed to remove pokemon from the list at runtime, as well as include any number of static pokemon they want included on the team. The program uses my custom ranking (Power level) that ranges from 1-17 which is determined from the type combinations of the pokemon on the team. Basically, there are three measurements to this power level component: weakness, resistance, and coverage. A pokemon is weak to a type that is super-effective against it, and resists a type that is not very effective against it. A pokemon has coverage against a type if they can deal super-effective against it. The teams power level is a point for every type it covers (max 17 since there are 17 types), and subtracts points for every type where the total weaknesses are greater than the total resistances against that type. Personal use of teams created by the Finder have been very useful to me personally.

Run the program using ./FindTeams <inputfile.txt> <outputfile.txt>

## Specifics
### The List
Users can create there own lists of pokemon to use in the Team Finder, but they must follow the specific format below...

PokemonName type1 type2(optional)

on each line. Examples can be found in the .txt documents provided.

The program creates structs of pokemon from these lists, chained together in a linked list. Once that list is complete, the program finds all of the unique typings in the list and creates a seperate list for the type combinations.

### The Typecharts
The program has the pokemon type combination chart hardcoded into it, and it uses that information to create any dual-type charts necessary (from the type combinations list). These charts are used to determine weaknesses, resistances, and coverages.

### The Calculations
The program uses 6 for loops (or less, depending on if the user wants to make sure a particular pokemon is included) that loop through the type combinations linked list and calculate the power level for every combination of 6 posssible. Only teams with the highest power level of that set of pokemon are saved, later to be written to the output file. In the future I hope to come up with a better solution to test all of the combinations of types. The program will also give the user an estimated time to completion (some lists can take quite a long time to calculate) and a progress bar (0-100%).

### Output
Once the program has the teams with the highest power level (it will output all teams it found of that power level), it will open the file provided by the user and write all of the teams inside, and will also include the power level of the teams in the file. Once this is done, the program cleans up the linked lists it made and exits.

