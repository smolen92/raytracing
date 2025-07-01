ray.out: ./obj/main.o ./obj/constant.o ./obj/sphere.o ./obj/hittable.o ./obj/hitlist.o ./obj/vec.o ./obj/ray.o ./obj/color.o ./obj/interval.o ./obj/camera.o
	g++ -o ray.out ./obj/main.o ./obj/vec.o ./obj/color.o ./obj/ray.o ./obj/sphere.o ./obj/hittable.o ./obj/hitlist.o ./obj/constant.o ./obj/interval.o ./obj/camera.o ./obj/material.o

./obj/main.o: ./src/main.cpp ./obj/hitlist.o ./obj/sphere.o ./obj/camera.o
	g++ -c ./src/main.cpp -o ./obj/main.o

./obj/color.o: ./src/color.h ./src/color.cpp ./obj/vec.o ./obj/interval.o
	g++ -c ./src/color.cpp -o ./obj/color.o

./obj/vec.o: ./src/vec.h ./src/vec.cpp ./obj/constant.o
	g++ -c ./src/vec.cpp -o ./obj/vec.o

./obj/ray.o: ./src/ray.h ./src/ray.cpp ./obj/vec.o
	g++ -c ./src/ray.cpp -o ./obj/ray.o

./obj/sphere.o: ./src/sphere.h ./src/sphere.cpp ./obj/material.o 
	g++ -c ./src/sphere.cpp -o ./obj/sphere.o

./obj/hittable.o: ./src/hittable.h ./src/hittable.cpp ./obj/ray.o ./obj/interval.o
	g++ -c ./src/hittable.cpp -o ./obj/hittable.o

./obj/hitlist.o:  ./src/hitlist.h ./src/hitlist.cpp ./obj/hittable.o
	g++ -c ./src/hitlist.cpp -o ./obj/hitlist.o

./obj/constant.o: ./src/constant.h ./src/constant.cpp 
	g++ -c ./src/constant.cpp -o ./obj/constant.o

./obj/interval.o: ./src/interval.h ./src/interval.cpp ./obj/constant.o
	g++ -c ./src/interval.cpp -o ./obj/interval.o

./obj/camera.o: ./src/camera.h ./src/camera.cpp ./obj/material.o
	g++ -c ./src/camera.cpp -o ./obj/camera.o

./obj/material.o: ./src/material.h ./src/material.cpp ./obj/hittable.o ./obj/color.o
	g++ -c ./src/material.cpp -o ./obj/material.o

.PHONY: doc clean clean-doc

doc:
	doxygen raytracing.dox

clean:
	rm -f ./obj/*.o

clean-doc:
	rm -r ./doc/*
