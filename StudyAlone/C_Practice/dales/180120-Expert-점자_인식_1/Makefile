all : solution user	

solution : main.cpp solution.cpp
	g++ main.cpp solution.cpp -std=c++17 -o solution

user : main.cpp user.cpp
	g++ main.cpp user.cpp -std=c++17 -o user 

clean : 
	rm user solution
	