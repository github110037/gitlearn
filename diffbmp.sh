#!/bin/bash
xxd -l 120 -c16 -g1 inputFile/pic.bmp > inpic.hex
xxd -l 120 -c16 -g1 outputFile/pic.bmp > outpic.hex
diff inpic.hex outpic.hex
