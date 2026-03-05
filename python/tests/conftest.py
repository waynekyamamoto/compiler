import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))

import cc


@pytest.fixture
def compile_and_run(tmp_path):
    """Return a helper that compiles C source with cc.py and runs the binary."""

    def _run(src: str) -> str:
        c_file = tmp_path / "test.c"
        c_file.write_text(src, encoding="utf-8")
        out_bin = tmp_path / "test_bin"

        rc = cc.main(["cc.py", "-o", str(out_bin), str(c_file)])
        assert rc == 0, f"cc.py compilation failed (rc={rc})"

        result = subprocess.run(
            [str(out_bin)],
            capture_output=True,
            text=True,
            timeout=10,
        )
        return result.stdout

    return _run


@pytest.fixture
def compile_and_run_rc(tmp_path):
    """Like compile_and_run but returns (stdout, returncode)."""

    def _run(src: str):
        c_file = tmp_path / "test.c"
        c_file.write_text(src, encoding="utf-8")
        out_bin = tmp_path / "test_bin"

        rc = cc.main(["cc.py", "-o", str(out_bin), str(c_file)])
        assert rc == 0, f"cc.py compilation failed (rc={rc})"

        result = subprocess.run(
            [str(out_bin)],
            capture_output=True,
            text=True,
            timeout=10,
        )
        return result.stdout, result.returncode

    return _run
