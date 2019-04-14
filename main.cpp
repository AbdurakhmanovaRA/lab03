#include <iostream>
#include <vector>
#include "histogram.h"

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}


vector<size_t> make_histogram(vector<double> numbers,size_t count){
    double min = numbers[0];
    double max = numbers[0];
    find_minmax(numbers, min, max);
    vector<size_t> bins(count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * count);
        if (bin == count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void show_histogram_txt(vector<size_t> bins, size_t width){
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > width;
     for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            size_t max_count = bins[0];
            for (size_t bin : bins)
            {
                if (bin > max_count)
                {
				max_count = bin;
                }
            }
            for (size_t bin : bins)
            {
                height = width * (static_cast<double>(bin) / max_count);  //max_asterisk
            }
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }
}

void svg_begin(double width, double height){
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg width='" << width << "' height='" << height << "' "
         << "viewBox='0 0 " << width << " " << height << "' "
         << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end(){
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text){
    cout << "<text x='"<< left << "' y='"<< baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black"){
    cout << "<rect x='"<< x << "' y='"<< y << "' width='" << width << "' height='" << height <<"' stroke='"
         << stroke << "' fill='" << fill <<"' />";
}

void show_histogram_svg(const vector<size_t>& bins, size_t width){
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;

    size_t max_count = 0;
    for (size_t bin : bins) {
        if (bin > max_count){
            max_count = bin;
        }
    }
    const bool scaling_needed = (max_count > width);


    for (size_t bin : bins) {

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)width / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        const double bin_width = 10 * height; //поменять
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#0400D1"); //изменить bin_width используя width
        top += BIN_HEIGHT;
    }
    svg_end();
}


int main() {
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // Обработка данных

    vector<size_t> bins = make_histogram(numbers, bin_count);

    size_t H_Width;			//выбранная пользователем ширина гистограммы
	cerr << "Enter histogram width: \n";
	cin >> H_Width;

	while ((H_Width < 7) || (H_Width > 80) || (H_Width < number_count/3 )) {
		if (H_Width < 7) {
			cerr << "histogram's width is less than 7. Enter again. \n";
		}
		if (H_Width > 80) {
			cerr << "histogram's width is more than 80. Enter again. \n";
		}
		if (H_Width < number_count / 3) {
			cerr << "histogram's width is less than third of number count. Enter again. \n";
		}
		cerr << "Enter histogram width: \n";
		cin >> H_Width;
	}


    // Вывод данных

    //show_histogram_txt(bins);
    show_histogram_svg(bins, H_Width);

    return 0;
}
