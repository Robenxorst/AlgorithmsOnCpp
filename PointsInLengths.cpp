//По данным n отрезкам необходимо найти множество точек минимального размера,
// для которого каждый из отрезков содержит хотя бы одну из точек.


#include <iostream>
#include <utility>// pair
#include <algorithm>// sort
#include <vector>

typedef std::pair <int, int> Segment;//отрезок

bool comp (Segment a, Segment b)
{
    return a.first < b.first;
}

std::vector <int> get_covering_set(std::vector <Segment> segments) {
    std::vector <int> result;

    sort(segments.begin(), segments.end());// сортируем отрезки по левому краю

    auto iterator = segments.cbegin();

    for (std::size_t i = 0; i < segments.size(); i++) {
        if (segments[i].second >= segments[i+1].first)
        {
            if (segments[i+1].second > segments[i].second)
                segments[i+1].second = segments[i].second;
            segments.erase(iterator + i);
            i--;
        }
    }

    for (std::size_t i = 0; i <= segments.size(); i++)
        result.push_back(segments[i].second);
    return result;
}

int main() {
    int segments_count;
    std::cin >> segments_count;
    std::vector <Segment> segments(segments_count);
    for (int i = 0; i < segments_count; i++) {
        std::cin >> segments[i].first >> segments[i].second;
    }

    std::cout << std::endl;
    std::vector <int> points = get_covering_set(segments);
    std::cout << points.size() << std::endl;
    for (std::size_t i = 0; i < points.size(); i++) {
        std::cout << points[i] << " ";
    }
    std::cout << std::endl;
}