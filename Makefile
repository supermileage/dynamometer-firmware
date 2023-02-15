include test/test.mk

test: $(TEST_OBJ) $(BIN_DIR) libwiringgcc
	@echo ' *** Building $@ *** '
	@g++ $(LFLAGS) $(TEST_OBJ) $(ARDUINO_LIB) $(INCLUDE_FLAGS) -o $(BIN_DIR)$@

run-tests: test
	@chmod +x ./test/bin/test
	./test/bin/test

pull-image:
	docker pull $(IMAGE)

libwiringgcc:
	@echo ' *** building $@ *** '
	@cd test/external/UnitTestLib && make libwiringgcc.a

clean: clean-test
	@rm -rf $(OUTPUT_DIR)

clean-test:
	@$(call clean-test-submodules)
	@rm -rf test/obj
	@rm -rf test/bin
	@rm -rf test/dep

define print
	@echo ''
	@echo '*** $(1) ***'
	@echo ''
endef

-include $(DEPENDENCIES)