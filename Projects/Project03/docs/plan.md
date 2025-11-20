# Project 03 Plan: CSV Table Sorter

## Goals
- Implement a CLI tool that sorts a database CSV by multi-column criteria specified in a separate sort CSV and writes the result to an output CSV.
- Support variable numbers of rows/columns and arbitrary column names.
- Data types for comparisons: string, int, float. Orders: ascend or descend.
- Use a stable sorting algorithm so equal keys keep their original relative order.

## Command-line interface
- Program name: `p3`
- Args: `./p3 <database.csv> <sort.csv> <output.csv>`
- Exit with non-zero on file open/parse errors (minimal validation per notes assume valid input).

## Data model
- `Header`: `vector<string>` of column names from first row of database.
- `Row`: `vector<string>` fields (as parsed, raw strings).
- `Table`: `struct { vector<string> header; vector<vector<string>> rows; unordered_map<string,size_t> col_index; }`.
- `SortCriterion`: `{ size_t col; enum Order {Asc, Desc}; enum Type {Str, Int, Float}; }`.
- `Criteria`: `vector<SortCriterion>` preserving the order from sort.csv (top to bottom is primary to tertiary...).

## Parsing
- Use `std::getline` to read lines.
- For CSV fields, use a simple split on `','` as shown in the instructor note since inputs are assumed valid and unquoted.
  - Pseudocode:
    - `while (getline(file, line)) { istringstream iss(line); while (getline(iss, field, ',')) fields.push_back(trim(field)); }`
- Database CSV:
  - First line → `header`, build `col_index` map.
  - Each remaining line → push to `rows` as `vector<string>`.
- Sort CSV:
  - Each line has 3 values: `column_name`, `order`, `type`.
  - Map `column_name` to index via `col_index`. Store `order` and `type`.

## Comparison helpers
- `trim` to remove surrounding spaces from fields.
- `to_int`/`to_float` using `std::stoi`/`std::stof` with basic try/catch; on failure, treat as 0 or fall back to lexical compare per “assume valid input”.
- `compare(a, b, Type, Order)`:
  - If `Type::Str`: lexical compare (`locale`-agnostic, use `<` on `std::string`).
  - If `Type::Int`: parse `long long` then compare.
  - If `Type::Float`: parse `double` then compare.
  - Apply `Order` by flipping sign for `Desc`.
- Multi-key comparator:
  - Iterate over `Criteria` in order; for each, compare the row fields at `col` with `compare`. If non-zero, return result; else continue. If all equal, return 0.

## Sorting
- Implement merge sort manually to ensure stability as required.
- Merge sort is inherently stable and has O(n log n) time complexity.
- Implementation approach:
  - `merge_sort(vector<vector<string>>& rows, int left, int right, comparator)`:
    - Base case: if `left >= right`, return.
    - Recursive case: find `mid`, recursively sort left and right halves, then merge.
  - `merge(vector<vector<string>>& rows, int left, int mid, int right, comparator)`:
    - Create temporary vectors for left and right subarrays.
    - Merge back into `rows` using the multi-key comparator.
    - When elements are equal, preserve original order (left subarray element comes first).

## Output
- Write header to `output.csv` exactly as read (comma-joined).
- Write each sorted row as comma-joined fields in the same column order as header.

## Build and run
- Example (from instructions):
  - Build: `g++ p3.cpp -Wall -Wuninitialized -std=c++17 -o p3.out`
  - Run: `./p3.out database.csv sort.csv output.csv`
- Repository defaults: place main in `src/p3.cpp` if preferred; adjust paths in README/Makefile later if added.

## Testing
- Create `docs/examples/` or use root-level sample files matching the screenshots:
  - `database.csv` and `sort.csv` per image.
  - Expected `output.csv` per image.
- Add additional tests:
  - Differing column orders.
  - All-string sorts; numeric sorts with negatives and floats.
  - Equal-key scenarios to verify stability.

## Performance considerations
- Single pass parses; avoid per-compare string trims/parses:
  - Pre-trim all fields during parsing.
  - For numeric columns used in criteria, optionally precompute parsed values caches:
    - `vector<vector<long long>> int_cache` and `vector<vector<double>> float_cache` aligned with rows for referenced columns only.
    - Only worth adding if large datasets observed; start simple then optimize.
- Avoid copying rows during compare; comparator accesses by index.

## Edge cases and assumptions
- Inputs are valid CSVs without quoted commas (per notes). If encountered, behavior unspecified.
- Column names in sort.csv must exist in database header.
- Case-insensitive match for `ascend`/`descend` and `string|int|float`.
- Missing/empty fields compared as empty string or zero for numeric (documented behavior).

## Implementation steps
1. Read args and open files.
2. Parse database header and rows; build `col_index`.
3. Parse sort criteria; validate columns; normalize order/type tokens.
4. Implement comparator using `Criteria`.
5. `stable_sort` rows.
6. Write output CSV.
7. Manual test with provided examples; diff against expected.
8. Optional: add Makefile and unit tests (e.g., GoogleTest or simple shell checks).

## Nice-to-haves (time permitting)
- Robust CSV with quoted fields via a small CSV parser.
- Configurable delimiter.
- Better error messages and exit codes.
