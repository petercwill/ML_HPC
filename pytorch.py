import pandas as pd
import time
import os
import numpy as np
import matplotlib.pyplot as plt
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms, utils
from PIL import Image
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.autograd import Variable
import torch
from cProfile import Profile
from pstats import Stats

class PicDataset(Dataset):
    """picture dataset."""

    data_aug_time = 0

    def __init__(self, label_file, pic_file, root_dir):
        """
        Args:
            label_file (string): Path to the csvfile with tag-label pairings.
            pic_file (string): Path to the csv file with names and tags.
            root_dir (string): Directory with all the images.
            transform (callable, optional): Optional transform to be applied
                on a sample.
        """
        labels = {}

        with open(label_file, 'r') as f:
            for l in f.readlines():
                tag, label = l.split(" ")
                labels[int(tag)] = label.strip('\n')

        self.labels = labels
        self.pics_frame = pd.read_csv(pic_file)
        self.root_dir = root_dir
        self.tf = transforms.Compose([
            transforms.Resize((32,32)),
            transforms.ToTensor(),
        ])

    def __len__(self):
        return len(self.pics_frame)

    def io(self, idx):
        img_name = os.path.join(self.root_dir,
                                self.pics_frame.iloc[idx, 0])+".jpg"
        img = Image.open(img_name)
        tag = self.pics_frame.iloc[idx, 1]
        label = self.labels[tag]
        sample = {'image': image, 'tag': tag, 'label':label}
        return(img)

    def preprocess(self, sample):
        img = self.tf(sample['img'])
        img = img[:3,:,:]
        sample['img'] = img
        return sample

    def __getitem__(self, idx):

        sample = io(idx)
        new_sample = self.preprocess(img)
        return new_sample


class PicClassifier(nn.Module):

    def __init__(self, num_labels, batch_size):
        super(PicClassifier, self).__init__()

        self.batch_size = batch_size
        self.layer1 = nn.Linear(3072, 1024)
        self.layer2 = nn.Linear(1024, 256)
        self.layer3 = nn.Linear(256, num_labels)

    def forward(self, x):
        x = x.view(self.batch_size, 3072)
        x = F.relu(self.layer1(x))
        x = F.relu(self.layer2(x))
        x = F.softmax(self.layer3(x), dim=0)
        return x

LABEL_FILE = "/scratch/am9031/CSCI-GA.3033-023/kaggleamazon/labels.txt"
TRAIN_FILE = "/scratch/am9031/CSCI-GA.3033-023/kaggleamazon/train.csv"
TEST_FILE = "/scratch/am9031/CSCI-GA.3033-023/kaggleamazon/test.csv"
PIC_DIR = "/scratch/am9031/CSCI-GA.3033-023/kaggleamazon/train-jpg"
BATCH_SIZE = 100

def imshow(img):
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1,2,0)))

def main():

    train_dataset = PicDataset(LABEL_FILE, TRAIN_FILE, PIC_DIR)
    test_dataset = PicDataset(LABEL_FILE, TEST_FILE, PIC_DIR)
    train_dl = DataLoader(
        train_dataset, batch_size=BATCH_SIZE, num_workers=1
    )
    test_dl = DataLoader(
        test_dataset, batch_size=BATCH_SIZE, num_workers=1
    )
    picClassifier = PicClassifier(num_labels = 17,
                                  batch_size=BATCH_SIZE).cuda() 
    
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(picClassifier.parameters(), lr=.01, momentum=.9)
    print(torch.cuda.is_available()) 

    dl_tot_time = 0
    epoch_start_time = time.monotonic() 

    for epoch in range(1):

        running_loss = 0.0
        dl_start_time = time.monotonic()
        for i, data in enumerate(train_dl, 0):

            dl_end_time = time.monotonic()
            dl_tot_time += (dl_end_time - dl_start_time)

            inputs = Variable(data['image']).cuda()
            tags = Variable(data['tag']).cuda()
            #labels = data['label']

            optimizer.zero_grad()
            outputs = picClassifier(inputs)  
            loss = criterion(outputs, tags)
            loss.backward()
            optimizer.step()

            running_loss += loss.data[0]
            if ((i % 20) == 19):
                print('[%d, %5d] loss: %.3f' %
                      (epoch +1, i + 1, running_loss / 20))
                running_loss = 0.0
           
if __name__ == "__main__":
    prof = Profile()
    main()
    prof.diable()
    prof.dump_stats('pytorch.stats')

    with open('pytorch_stats.txt', 'wt') as output:
        stats = Stats('pytorch.stats', stream=output)
        stats.sort_stats('cumulative', 'time')
        stats.print_stats()





