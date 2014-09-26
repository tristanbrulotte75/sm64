from collections import defaultdict
import math
import os
import sys

from PIL import Image

def sigma(ls):
    mean = sum(ls)/len(ls)
    variance = sum([(item - mean)**2 for item in ls])/len(ls)
    return (mean, math.sqrt(variance))

def condensed_frame(frame):
    d = {}

    for index, value in enumerate(frame):
        if value != 0:
            d[index] = value

    return d

# should this just average the frame differences?
def frame_diff(frame1, frame2):
    sum = 0.0
    count = 0

    max_diff = 0

    for i in range(len(frame1)):
        if frame1[i] != 0:
            diff = abs(frame1[i] - frame2[i])

            max_diff = max(max_diff, diff)

            sum += diff**2
            count += 1

    return (math.sqrt(sum/count), max_diff)

def save_frame(frame, f):
    im = Image.new('RGB', (80, 33), 'white')
    rgb = []
    for i in range(0, len(frame), 3):
        rgb.append((frame[i+2], frame[i + 1], frame[i]))
    im.putdata(rgb)
    im.save(f)

class StarData(object):
    cache = {}

    def __init__(self, star_number):
        if star_number in self.cache:
            self.data = self.cache[star_number].data
            return

        self.data = defaultdict(list)

        for line in open('data/star_%s.dat' % star_number, 'r'):
            # frame: sample number
            # index: rgb index
            frame, row, col, index, value = map(int, line.strip().split('\t'))
            self.data[index].append(value)

        self.cache[star_number] = self

    def nth_frame(self, n):
        return [self.data[frame][n] for frame in self.data]

    def frames(self):
        count = len(self.data[0])

        for i in range(count):
            yield [self.data[j][i] for j in self.data]

    def stats(self):
        return StarStats(self)

class StarStats(object):
    def __init__(self, star_data):
        self.rgb_stats = []

        for rgb_index in star_data.data:
            mean, std = sigma(star_data.data[rgb_index])
            self.rgb_stats.append((mean, std))

    def filtered_frame(self, error):
        frame = []

        for (mean, std) in self.rgb_stats:
            if std < error:
                frame.append(mean)
            else:
                frame.append(0)

        return frame

def random_frame(star_number):
    return StarData(star_number).nth_frame(40)

def save_filtered_frames():
    try:
        os.mkdir('filtered')
    except OSError:
        pass

    for i in range(121):
        print i
        stats = StarData(i).stats()
        for j in range(1, 21):
            save_frame(stats.filtered_frame(j),
                       'filtered/filtered_%s_%s.png' % (i, j))

def compare_frames():
    out = []

    for i in range(121):
        filtered_frame = StarData(i).stats().filtered_frame(4)
        for j in range(121):
            sys.stderr.write('%s %s\n' % (i, j))
            most_similar = 256.0
            for frame in StarData(j).frames():
                diff = frame_diff(filtered_frame, frame)
                most_similar = min(most_similar, diff[0])
            out.append((i, j, most_similar))

    out.sort(key=lambda k: k[2], reverse=True)

    print '\n'.join(map(str, out))

if __name__ == '__main__':
    compare_frames()
    #save_filtered_frames()
    #print frame_diff(StarStats(StarData(1)).filtered_frame(4), random_frame(0))
