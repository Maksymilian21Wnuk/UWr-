import cat_app
import asyncio
import subprocess

from PIL import Image, ImageDraw, ImageFont

def add_text_to_image(input_image_path, output_image_path, text):
    
    image = Image.open(input_image_path)
    draw = ImageDraw.Draw(image)

    # Choose a font and size
    font = ImageFont.load_default()
    font_size = image.size[0] // 20
    print(font_size)
    font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", font_size)

    # Set the position to place the text
    text_position = (10, 10)

    # Set the text color
    text_color = (255, 255, 255)  # White

    # Add text to the image
    draw.text(text_position, text, font=font, fill=text_color)

    # Save the modified image
    image.save(output_image_path)

# open file with linux's command xdg-open
def open_file(file_name):
    try:
        subprocess.run(["xdg-open", file_name], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")   

def main():
    items = asyncio.run(cat_app.routine())
    quote = items['quote']
    file_name = (items['img_data'])[2]
    add_text_to_image(file_name, file_name, quote)
    print(f"Text added to cat image: {file_name}")
    open_file(file_name)

if __name__ == "__main__":
    main()