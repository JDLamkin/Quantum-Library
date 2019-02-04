# Quantum-Library
Ongoing library for use with quantum computation (simulators, algorithms, languages, etc.).

## QPU
A simple quantum computer simulator. Mimics the functionality of an N-bit "quantum processing
unit" supporting the following atomic operations on its qubits:
 * `H` = Hadamard Transform
 * `X` = Pauli X Gate / Bit Flip
 * `Y` = Pauli Y Gate
 * `Z` = Pauli Z Gate / Phase Flip
 * `S` = 1/4 Phase Gate
 * `T` = 1/8 Phase Gate
 * `RX(t)` = X Rotation by t parts of a circle
 * `RY(t)` = Y Rotation by t parts of a circle
 * `RZ(t)` = Z Rotation by t / Phase Shift of t
 * `CX` = CNOT Gate
 * `CCX` = CCNOT Gate / Toffoli Gate
