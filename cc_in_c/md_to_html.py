import markdown
import sys

with open("BLOG_DRAFT.md", "r") as f:
    md = f.read()

html_body = markdown.markdown(md, extensions=["tables", "fenced_code"])

html = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>I built a self-hosting C compiler with Claude</title>
<style>
  body {{
    font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Helvetica, Arial, sans-serif;
    max-width: 720px;
    margin: 40px auto;
    padding: 0 20px;
    line-height: 1.7;
    color: #1a1a1a;
    font-size: 17px;
  }}
  h1 {{
    font-size: 2em;
    line-height: 1.2;
    margin-bottom: 0.3em;
  }}
  h2 {{
    font-size: 1.4em;
    margin-top: 2em;
    border-bottom: 1px solid #ddd;
    padding-bottom: 0.3em;
  }}
  p {{
    margin: 1em 0;
  }}
  code {{
    background: #f4f4f4;
    padding: 2px 6px;
    border-radius: 3px;
    font-size: 0.9em;
  }}
  pre {{
    background: #f4f4f4;
    padding: 16px;
    border-radius: 6px;
    overflow-x: auto;
    line-height: 1.4;
  }}
  pre code {{
    background: none;
    padding: 0;
  }}
  table {{
    border-collapse: collapse;
    width: 100%;
    margin: 1.5em 0;
  }}
  th, td {{
    border: 1px solid #ddd;
    padding: 10px 14px;
    text-align: left;
  }}
  th {{
    background: #f4f4f4;
    font-weight: 600;
  }}
  tr:nth-child(even) {{
    background: #fafafa;
  }}
  strong {{
    font-weight: 600;
  }}
  a {{
    color: #0066cc;
    text-decoration: underline;
  }}
  ul {{
    padding-left: 1.5em;
  }}
  li {{
    margin: 0.4em 0;
  }}
  @media print {{
    body {{
      font-size: 12pt;
      max-width: none;
      margin: 0;
    }}
  }}
</style>
</head>
<body>
{html_body}
</body>
</html>
"""

with open("BLOG_DRAFT.html", "w") as f:
    f.write(html)

print("Written to BLOG_DRAFT.html")
