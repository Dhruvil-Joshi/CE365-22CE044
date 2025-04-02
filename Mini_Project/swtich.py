import re

def analyze_switch_case(code):
    """
    A comprehensive switch case syntax analyzer that checks if a switch case statement is properly formed.
    
    Args:
        code (str): A string containing the switch case code to analyze
    
    Returns:
        dict: Analysis results including validity and detailed errors found
    """
    code = code.strip()
    
    result = {
        "valid": True,
        "errors": [],
        "structure": {
            "has_switch": False,
            "has_condition": False,
            "has_opening_brace": False,
            "has_closing_brace": False,
            "case_count": 0,
            "has_default": False,
            "break_count": 0,
            "cases_with_breaks": 0
        }
    }
    
    switch_pattern = re.compile(r'switch\s*\(\s*[a-zA-Z0-9_]+\s*\)')
    if "switch" not in code:
        result["valid"] = False
        result["errors"].append("Missing 'switch' keyword")
    else:
        result["structure"]["has_switch"] = True
        if not switch_pattern.search(code):
            result["valid"] = False
            result["errors"].append("Invalid switch syntax: missing or malformed condition")
        else:
            result["structure"]["has_condition"] = True
    
    if "{" not in code:
        result["valid"] = False
        result["errors"].append("Missing opening brace '{'")
    else:
        result["structure"]["has_opening_brace"] = True
        
    if "}" not in code:
        result["valid"] = False
        result["errors"].append("Missing closing brace '}'")
    else:
        result["structure"]["has_closing_brace"] = True
    
    if code.count("{") != code.count("}"):
        result["valid"] = False
        result["errors"].append(f"Unbalanced braces: {code.count('{')} opening vs {code.count('}')} closing")
    
    lines = code.split("\n")
    case_pattern = re.compile(r'^\s*case\s+\S+\s*:')
    default_pattern = re.compile(r'^\s*default\s*:')
    
    in_case_block = False
    current_case_has_break = False
    case_line_numbers = []
    case_values = set()
    case_spelling_variants = ["case", "Case", "CASE"]
    
    for i, line in enumerate(lines):
        line = line.strip()

        for variant in case_spelling_variants:
            if variant in line and not line.startswith("case ") and not "//".join(variant) in line:
                result["valid"] = False
                result["errors"].append(f"Possible misspelled 'case' keyword at line {i+1}: '{line}'")
        
        if line.startswith("case "):
            if not case_pattern.match(line):
                result["valid"] = False
                result["errors"].append(f"Invalid case syntax at line {i+1}: '{line}' (missing value or colon)")
            else:
                result["structure"]["case_count"] += 1
                case_line_numbers.append(i+1)
                
                try:
                    case_value_match = re.search(r'case\s+(\S+)\s*:', line)
                    if case_value_match:
                        case_value = case_value_match.group(1)
                        
                        if case_value in case_values:
                            result["valid"] = False
                            result["errors"].append(f"Duplicate case value '{case_value}' at line {i+1}")
                        case_values.add(case_value)
                        
                        if not (case_value.isdigit() or 
                                (case_value.startswith('"') and case_value.endswith('"')) or
                                (case_value.startswith("'") and case_value.endswith("'")) or
                                case_value in ['true', 'false', 'null']):
                            result["valid"] = False
                            result["errors"].append(f"Potentially invalid case value '{case_value}' at line {i+1}")
                except Exception as e:
                    result["valid"] = False
                    result["errors"].append(f"Error parsing case value at line {i+1}: {str(e)}")
                
                if in_case_block and not current_case_has_break:
                    result["valid"] = False
                    result["errors"].append(f"Missing break statement before case at line {i+1}")
                
                in_case_block = True
                current_case_has_break = False

        elif line.startswith("default ") and ":" in line and not line.strip() == "default:":
            value_in_default = line.split("default")[1].split(":")[0].strip()
            if value_in_default:
                result["valid"] = False
                result["errors"].append(f"Invalid default syntax at line {i+1}: default should not have a value '{value_in_default}'")
        
        elif "default:" in line:
            if not default_pattern.match(line):
                result["valid"] = False
                result["errors"].append(f"Invalid default syntax at line {i+1}: '{line}'")
            else:
                if result["structure"]["has_default"]:
                    result["valid"] = False
                    result["errors"].append(f"Multiple default statements found at line {i+1}")
                
                result["structure"]["has_default"] = True
                
                if in_case_block and not current_case_has_break:
                    result["valid"] = False
                    result["errors"].append(f"Missing break statement before default at line {i+1}")
                
                in_case_block = True
                current_case_has_break = False
        
        elif "break;" in line:
            result["structure"]["break_count"] += 1
            if in_case_block:
                current_case_has_break = True
                result["structure"]["cases_with_breaks"] += 1
        
        elif "break " in line and "break;" not in line:
            result["valid"] = False
            result["errors"].append(f"Malformed break statement at line {i+1}: '{line}' (should be 'break;')")
    
    if in_case_block and not current_case_has_break:
        result["valid"] = False
        result["errors"].append("Missing break statement in the last case/default")
    
    if result["structure"]["case_count"] == 0:
        result["valid"] = False
        result["errors"].append("No 'case' statements found")
    
    if result["structure"]["cases_with_breaks"] < result["structure"]["case_count"] + (1 if result["structure"]["has_default"] else 0):
        result["errors"].append("Not all cases have break statements")
    try:
        switch_start = code.index("switch")
        first_brace = code.index("{", switch_start)
        last_brace = code.rindex("}")
        
        switch_block = code[first_brace:last_brace+1]
        for pattern in ["case", "default:"]:
            if pattern in code[:switch_start] or (last_brace+1 < len(code) and pattern in code[last_brace+1:]):
                result["valid"] = False
                result["errors"].append(f"'{pattern}' statement found outside of switch block")
    except ValueError:
        pass
    
    return result

if __name__ == "__main__":
    example_code = """
    switch (value) {
        case 1:
            console.log("One");
            break;
        case 2:
            console.log("Missing colon and value");
            break;
        case 3:
            console.log("Missing colon");
            break;
        case 4:
            console.log("Missing break");
            break;
        default:
            console.log("Other");
            break;
    }
    """
    
    result = analyze_switch_case(example_code)
    print("Analysis Result:")
    print(f"Valid: {result['valid']}")
    print(f"Errors:")
    for error in result['errors']:
        print(f"  - {error}")
    print("Structure Details:")
    for key, value in result["structure"].items():
        print(f"  {key}: {value}")

        example_code = """
    switch (value) {
        case 1:
            console.log("One");
            break;
        Case 2:
            console.log("Incorrect case capitalization");
            break;
        case 2:
            console.log("Duplicate case value");
            break;
        case "string":
            console.log("String value");
            break;
        case invalidValue:
            console.log("Invalid case value");
            break;
        case 4
            console.log("Missing colon");
        case 5:
            console.log("Missing break");
        default value:
            console.log("Default with invalid value");
            break;
        default:
            console.log("Second default statement");
            break
    }
    """