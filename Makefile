CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2
SRC      := $(wildcard src/*.cpp src/schedulers/*.cpp)
BIN      := build/schedulers

$(BIN): $(SRC) $(wildcard src/*.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

# Run every scheduler on its example workload from data/.
demo: $(BIN)
	@for a in fcfs sjf srtf rr mlfq; do \
		echo "===== $$a (data/$${a}_example.txt) ====="; \
		./$(BIN) $$a data/$${a}_example.txt; echo; \
	done

clean:
	rm -rf build

.PHONY: demo clean
