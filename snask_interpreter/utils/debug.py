DEBUG_MODE = False  # ou False, como preferir

def debug_print(*args, **kwargs):
    if DEBUG_MODE:
        print("[DEBUG]", *args, **kwargs)
