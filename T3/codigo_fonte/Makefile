CC = g++
CFLAGS = -g -Wall -ansi -pedantic -std=c++17
INCLUDES_CC = ${wildcard *.cc}
# INCLUDES_H = ${wildcard *.h}
OUT = ${DIR}/main
RM= rm -rf
DIR=build

# Compiling
all: clean mk_dir
	@ echo 'Building executable file ${OUT}'
	@ ${CC} ${CFLAGS} ${INCLUDES_CC} -o ${OUT}
	@ echo 'Executable file ${OUT} created!'

# Checking using valgrind
# --leak-check=<no|yes|summary|full>
# --show-leak-kinds=all
check:
	valgrind  --leak-check=summary --show-leak-kinds=all ${OUT}

# Removing build directory
clean:
	@ echo ''${DIR}' dir deleted!'
	@ ${RM} ${DIR}

# Running program
run:
	@ ./${OUT}

# Making dir
mk_dir:
	@ mkdir -p ${DIR}
	@ echo ''${DIR}' dir created!'

#This submission command was copied from INE5410 exercises
submission: clean
	@SUBNAME=$$(basename "$$(pwd)"); \
		echo cd ..\; tar zcf "$$SUBNAME.tar.gz" "$$SUBNAME"
	@SUBNAME=$$(basename "$$(pwd)"); \
		cd ..; \
		rm -fr "$$SUBNAME.tar.gz"; \
		tar zcf "$$SUBNAME.tar.gz" "$$SUBNAME"
	@echo "Criado pacote \"$$(pwd).tar.gz\" para submissão"