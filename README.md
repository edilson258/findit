# Local Search Engine with TF-IDF Algorithm (C Version)
Inspired by [Tsoding Daily](https://youtu.be/hm5xOJiVEeg?si=6kUwIMQjILgsdRs6)

## Overview

This GitHub project houses a powerful local search engine implemented in C, leveraging the TF-IDF (Term Frequency-Inverse Document Frequency) algorithm to retrieve the most relevant documents from a local corpus. Whether you're searching for files on your computer or looking to incorporate this engine into your own C-based application, this repository provides a robust solution.

## Features

- Efficient indexing of local documents for rapid searching.
- Calculation of TF-IDF scores to rank documents by relevance.
- Customizable parameters for fine-tuning search results.
- Supports a wide range of document types, including text, PDF. (.txt for now).
- User-friendly command-line interface (CLI) for easy interaction.
- Makefile for simple compilation and execution.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- A C compiler (CLANG) installed.
- Git installed to clone this repository.

### Installation

1. Clone this repository:

```shell
git clone https://github.com/edilson258/findit.git
```

2. Navigate to the project directory:

```shell
cd findit
```

### Usage

#### Compilation

1. Compile the project using the provided Makefile:

```shell
make
```

#### Indexing Your Local Corpus and Searching

1. To index your local corpus and search within the index run the following command:

```shell
./findit <path/to/your/corpus> <query>
```
##### Example
```shell
./findit samples "tell me about Blockchain"
```

- The indexer will analyze and store the documents in a format optimized for fast retrieval.
- The search engine will return a list of relevant documents based on the TF-IDF algorithm.

#### Customization

You can customize the search behavior by adjusting parameters in the source code or via command-line arguments.

## Contributing

We welcome contributions from the community! If you'd like to contribute to this C-based project, please follow our [contributing guidelines](CONTRIBUTING.md).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Special thanks to [Edilson Pateguana](https://github.com/edilson258) for their valuable contributions.

## Contact

If you have any questions or feedback, feel free to reach out to us at [developeredilson@gmail.com](mailto:developeredilson@gmail.com).

---

Thank you for using our local search engine with TF-IDF implemented in C! We hope you find it useful and welcome your feedback and contributions. Happy searching!
