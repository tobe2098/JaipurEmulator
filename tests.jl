include("jaipur.jl")
import .Sys
import Libdl

# Determine the appropriate library file name based on the operating system
libname = "libjaipur"

if Sys.iswindows()
    library_name=libname*".dll"
    library_name = joinpath("bin", library_name)
elseif Sys.islinux()
    library_name = "./bin/libjaipur.so"
else
    library_name = "./bin/libjaipur.dylib"
end

# Check if the library file exists and try to load it
if isfile(library_name)
    # println("File exists at $libname")
    global library = Libdl.dlopen_e(library_name)
    if library == C_NULL
        println("Failed to load library.")
    else
        println("Library loaded successfully.")
        print("Testing the dynamic library linking...")

        local c_array = Vector{Cint}(undef, 7)
        local test_result=0
        for i in 1:7
            c_array[i] = i
            test_result+=i
        end

        sumOfCardsGroup_func = Libdl.dlsym(library, :sumOfCardsGroup)
        result = test_result==ccall(sumOfCardsGroup_func, Cint, (Ptr{Cint}, Cint), c_array, 0)
        if  !result
            error("The test of the dynamic library failed")
        end
        print("OK\n")
    end
else
    error("Library not found at $library_name")
end
print("Testing pointer allocation...")
game_data_ptr=create_game_data(Cuint(42))
if game_data_ptr == C_NULL
    error("Failed to allocate GameData struct in the library test")
end
print("OK\n")
## Test loading the data into Julia struct
print("Testing unsafe_load'ing...")
game_data = unsafe_load(game_data_ptr)
if game_data.seed!=Cuint(42) || game_data.init!=1
    error("The data was not properly unsafe_load'ed into Julia")
end
print("OK\n")
## Test the data was properly initialized
print("Testing data initialization...")
flag=process_game_action(game_data_ptr, String[],true)
game_data = unsafe_load(game_data_ptr)
if flag&DATA_OKAY_FLAG==0 || game_data.seed!=Cuint(42)
    # flag_identifiers(flag)
    error("The data was not properly initialized in the library test")
end
print("OK\n")

## Test the exchange function works
print("Testing exchange action...")
action=EXCHANGE_STR
hand_card=LEATHER_STR
market_card=SPICE_STR
action_arr=[action,hand_card,market_card]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0||game_data.hand_plB[spices]!=Cint(2)
    # flag_identifiers(flag)
    error("The exchange action test failed in the library test")
end
print("OK\n")
## Test the take camels function works
print("Testing take all camels action...")
action=TAKE_CAMELS_STR
action_arr=[action]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0 || game_data.hand_plA[camels]!=Cint(3)
    # flag_identifiers(flag)
    error("The take all camels action test failed in the library test")
end
print("OK\n")

## Test the take goods function works
print("Testing take single good action...")
action=TAKE_GOOD_STR
market_card=DIAMOND_STR
action_arr=[action,market_card]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0||game_data.hand_plB[diamonds]!=Cint(2)
    flag_identifiers(flag)
    error("The take single good action test failed in the library test")
end
print("OK\n")

## Test the sell goods function works
print("Testing sell goods action...")
action=SELL_GOOD_STR
hand_card=LEATHER_STR
number_of_sold_cards=string(2)
action_arr=[action,hand_card,number_of_sold_cards]
flag=process_game_action(game_data_ptr, action_arr,true)
game_data = unsafe_load(game_data_ptr)
if  flag&DATA_OKAY_FLAG==0||flag&TURN_HAPPENED_FLAG ==0 || game_data.playerA.points!=Cint(7)
    flag_identifiers(flag)
    error("The sell goods action test failed in the library test")
end
print("OK\n")

# println("game_data: $game_data")

## Test round management
print("Testing round over state...")
flag|=ROUND_OVER
round_management(game_data_ptr, flag,() -> nothing,() -> nothing,() -> nothing,() -> nothing)
game_data=unsafe_load(game_data_ptr)
if game_data.turn_of!=PLAYER_A_NUM || game_data.playerB.seals!=1 
    error("The test of round over failed in the library test")
end
print("OK\n")

print("Testing game over state...")
flag|=ROUND_OVER
flag|=GAME_OVER
flag|=PLAYER_A_WINS
round_management(game_data_ptr, flag,() -> nothing,() -> nothing,() -> nothing,() -> nothing)
game_data=unsafe_load(game_data_ptr)
if  game_data.playerB.seals!=0 
    error("The test of round over failed in the library test")
end
print("OK\n")

print("Testing pointer freeing...")
game_data_ptr=free_game_data(game_data_ptr)
if game_data_ptr!=C_NULL
    error("The pointer was not properly freed.")
end
print("OK\n")
println("All the tests passed.")
