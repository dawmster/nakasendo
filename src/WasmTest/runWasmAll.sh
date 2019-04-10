# big numbers generator
docker run --rm -v $(pwd):/src -v /home/osboxes/secLibFroWasm:/home/osboxes/secLibFroWasm -u 1000 trzeci/emscripten emcc -O3 BigNumbers/BigNumAPI.cpp BigNumbers/BigNumbers.cpp BigNumbers/BigNumbersImpl.cpp -o BigNumbers.js -s EXPORTED_FUNCTIONS='["_BNRandomHex", "_BNRandomDec","_BNRandomHexWithSeed","_BNRandomDecWithSeed","_addFromDec","_addFromHex","_subFromHex","_subFromDec"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -I. -I/home/osboxes/secLibFroWasm -I/home/osboxes/secLibFroWasm/openssl/include -L/home/osboxes/secLibFroWasm/openssl -std=c++11 -g -pthread -lssl -lcrypto

# MessageHash generator
docker run --rm -v $(pwd):/src -v /home/osboxes/secLibFroWasm:/home/osboxes/secLibFroWasm -u 1000 trzeci/emscripten emcc -O3 MessageHash/MessageHashAPI.cpp MessageHash/MessageHash.cpp MessageHash/MessageHashImpl.cpp -o MessageHash.js -s EXPORTED_FUNCTIONS='["_HashMsgSHA256", "_HashMsg","_ListHashFunc"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -I. -I/home/osboxes/secLibFroWasm -I/home/osboxes/secLibFroWasm/openssl/include -L/home/osboxes/secLibFroWasm/openssl -std=c++11 -g -pthread -lssl -lcrypto

# Combine all into one lib
docker run --rm -v $(pwd):/src -v /home/osboxes/secLibFroWasm:/home/osboxes/secLibFroWasm -u 1000 trzeci/emscripten emcc -O3 MessageHash/MessageHashAPI.cpp MessageHash/MessageHash.cpp MessageHash/MessageHashImpl.cpp BigNumbers/BigNumAPI.cpp BigNumbers/BigNumbers.cpp BigNumbers/BigNumbersImpl.cpp -o CryptoBase.js -s EXPORTED_FUNCTIONS='["_HashMsgSHA256", "_HashMsg","_ListHashFunc","_BNRandomHex", "_BNRandomDec","_BNRandomHexWithSeed","_BNRandomDecWithSeed","_addFromDec","_addFromHex","_subFromHex","_subFromDec"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -I. -I/home/osboxes/secLibFroWasm -I/home/osboxes/secLibFroWasm/openssl/include -L/home/osboxes/secLibFroWasm/openssl -std=c++11 -g -pthread -lssl -lcrypto

