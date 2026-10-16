# Contributing to MK-56 Development Environment

Thank you for your interest in contributing!

## How to Contribute

### Reporting Issues

1. Check existing issues before creating new ones
2. Provide clear reproduction steps
3. Include system information (OS, compiler version)

### Pull Requests

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/my-feature`
3. Make your changes
4. Test thoroughly
5. Commit with clear messages
6. Push and create a PR

### Code Style

#### C Code
- Use C11 standard
- 4-space indentation
- Keep functions under 50 lines when possible
- Add comments for complex logic

- Opcodes live only in `common/mk56_isa.c`; never add a second table

#### Programs
- Include header comments describing purpose, input, output and source
  (book and page)
- Add `; @input` / `; @expect` lines so `make test` runs the program
- In `.mk56` listings, start each line with its `NN:` address

### Testing

```bash
make test
```

New emulator behaviour needs a test in `tests/test_core.c`, ideally an
example from the manual with its page number.

### Documentation

- Emulator behaviour must match the [manual](docs/manual/README.md); cite
  the page. Behaviour the manual does not describe is marked "inferred" in
  the code.
- Translation fixes: cite the page of the scan in `references/`.

## Attribution

All contributions are subject to the project's MIT License with attribution requirements. By contributing, you agree to these terms.

## Questions?

Open an issue for discussion.
