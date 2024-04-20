import pandas as pd

def format_arduino_data(input_file_path, output_csv_path):
    # Define the headers as specified
    headers = [
        "timestamp", "COavg", "CH4avg", "C2H5OHavg", "H2avg", "NH3avg", "NO2avg",
        "COmin", "CH4min", "C2H5OHmin", "H2min", "NH3min", "NO2min",
        "COmax", "CH4max", "C2H5OHmax", "H2max", "NH3max", "NO2max"
    ]

    # Initialize a list to hold the formatted data
    formatted_data = []

    # Open and process the input file
    with open(input_file_path, 'r') as file:
        for line in file:
            # Clean line and replace '->' with ',' if present
            line = line.strip().replace('->', ',')

            # Split by comma now to handle both delimiters
            parts = line.split(',')

            # Skip irrelevant lines
            if not line or "Warming up" in line or all(float(v) == 0.0 for v in parts[1:]):
                continue

            # Format data for DataFrame, assuming timestamp is first and data follows
            formatted_data.append(parts)

    # Convert the list of data into a DataFrame
    df = pd.DataFrame(formatted_data, columns=headers)

    # Save the DataFrame to a CSV file
    df.to_csv(output_csv_path, index=False)

    print(f"Data has been formatted and saved to {output_csv_path}")

# Example usage
input_file_path = '/content/20-4-gin.txt'  # Change this to your actual input file path
output_csv_path = '/content/20-4-gin.csv'  # Change this to your desired output file path

# Call the function with the paths
format_arduino_data(input_file_path, output_csv_path)

