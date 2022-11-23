def now(cur):
    return cur.execute("SELECT datetime('now', '+9 hours')").fetchone()[0]
