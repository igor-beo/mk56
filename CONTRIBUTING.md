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

#### Python Code
- Follow PEP 8
- Use type hints
- Add docstrings to functions

#### Assembly Examples
- Include header comments describing purpose, input, output
- Use meaningful label names
- Comment non-obvious operations

### Testing

```bash
# Test assembler
cd asm/assembler-c && make test

# Test emulator
cd asm/emulator && make test
```

### Documentation

- Update relevant docs when adding features
- Keep wiki pages in sync with code

## Attribution

All contributions are subject to the project's MIT License with attribution requirements. By contributing, you agree to these terms.

## Questions?

Open an issue for discussion.
