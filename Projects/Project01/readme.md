# Project 01 – Network Analyzer

## Overview
You are given a text file describing a network. Each line of the file contains three tokens:

1. Source network identifier
2. Destination network identifier
3. Bandwidth (integer Mb/s) from the source to the destination

Identifiers:

- May appear multiple times as sources and/or destinations
- Contain only letters and digits (case-insensitive)
- May be composed entirely of digits or entirely of letters (e.g., `123`, `abc`)

Your program must accept **two command-line arguments**:

1. The input filename
2. The output filename

All output should be directed to the specified output file.

## Output Requirements
1. List every unique identifier, **in order of first appearance**, converted to uppercase—one per line.
2. A **leaf identifier** is one that appears only as a source or only as a destination. If an identifier is a leaf, output only its uppercase name.
3. For every **non-leaf** identifier, output an additional line containing four fields separated by spaces:
   - Identifier in uppercase
   - Sum of outbound bandwidths ("from")
   - Sum of inbound bandwidths ("to")
   - Ratio `to/from` as a fixed two-decimal-place double

If there are no non-leaf identifiers, output only the list of uppercase identifiers.

## Example
### `input1.txt`
```
TCLDCR01 TCLCOT00 1000
TCLDCS02 TCLcot00 2000
northdat00 TCLCOT01 1000
NORTHREM1 NORTHDAT00 300
tcLCot00 alat0 1000
COKREM2 NORTHDAT00 100
TCLCOT01 ALAT0 1000
TCLCOT00 BNG4 1000
```

Run command:
```
./a.out input1.txt output.txt
```

### `output.txt`
```
TCLDCR01
TCLCOT00
TCLDCS02
NORTHDAT00
TCLCOT01
NORTHREM1
ALAT0
COKREM2
BNG4

TCLCOT00 2000 3000 1.50
NORTHDAT00 1000 400 0.40
TCLCOT01 1000 1000 1.00
```

## Notes
- Assume the input is valid.
- Match the sample formatting exactly (spacing, casing, decimal precision).
- Use C++ streams for all file I/O.
- Create your own additional tests beyond the provided sample.
- Downloadable example cases are available from the course site.
- A 1,000-line input file should finish within a few seconds; ensure your solution is efficient.
