import torch
import torch.nn as nn
import torch.nn.functional as F
        
class My_ResNet18(nn.Module):    
    def __init__(self,num_classes=10):
        super(My_ResNet18,self).__init__()
        cfg = [(3),(64),(128),(256),(512)]
        
        self.Conv_00 = nn.Conv2d(cfg[0],cfg[1],kernel_size=3, stride=1,padding=1,bias=False)
        
        self.Conv_01 = nn.Conv2d(cfg[1],cfg[1],kernel_size=3, stride=1, padding=1,bias=False)
    
        self.Conv_02 = nn.Conv2d(cfg[1],cfg[2],kernel_size=3,stride=2,padding=1,bias=False)
        self.Conv_03 = nn.Conv2d(cfg[2],cfg[2],kernel_size=3,stride=1,padding=1,bias=False)

        self.Conv_04 = nn.Conv2d(cfg[2],cfg[3],kernel_size=3,stride=2,padding=1,bias=False)
        self.Conv_05 = nn.Conv2d(cfg[3],cfg[3],kernel_size=3,stride=1,padding=1,bias=False)

        self.Conv_06 = nn.Conv2d(cfg[3],cfg[4],kernel_size=3,stride=2,padding=1,bias=False)
        self.Conv_07 = nn.Conv2d(cfg[4],cfg[4],kernel_size=3,stride=1,padding=1,bias=False)

        self.Bn_01 = nn.BatchNorm2d(cfg[1])
        self.Bn_02 = nn.BatchNorm2d(cfg[2])
        self.Bn_03 = nn.BatchNorm2d(cfg[3])
        self.Bn_04 = nn.BatchNorm2d(cfg[4])
        
        self.linear = nn.Linear(cfg[4],num_classes)
        self.shortcut_Conv_01 = nn.Conv2d(cfg[1],cfg[1],kernel_size=1,stride=1,bias=False)
        self.shortcut_Conv_02 = nn.Conv2d(cfg[1],cfg[2],kernel_size=1,stride=2,bias=False)
        self.shortcut_Conv_03 = nn.Conv2d(cfg[2],cfg[2],kernel_size=1,stride=1,bias=False)
        self.shortcut_Conv_04 = nn.Conv2d(cfg[2],cfg[3],kernel_size=1,stride=2,bias=False)
        self.shortcut_Conv_05 = nn.Conv2d(cfg[3],cfg[3],kernel_size=1,stride=1,bias=False)
        self.shortcut_Conv_06 = nn.Conv2d(cfg[3],cfg[4],kernel_size=1,stride=2,bias=False)
        self.shortcut_Conv_07 = nn.Conv2d(cfg[4],cfg[4],kernel_size=1,stride=1,bias=False)

    def forward(self,x):
        # first_Conv2d
        out = F.relu(self.Bn_01(self.Conv_00(x)))
        identity = out

        # Conv2d_Block_01
        out = F.relu(self.Bn_01(self.Conv_01(out)))
        out = self.Bn_01(self.Conv_01(out))
        out = F.relu(out + self.shortcut_Conv_01(identity))
        identity = out

        out = F.relu(self.Bn_01(self.Conv_01(out)))
        out = self.Bn_01(self.Conv_01(out))
        out = F.relu(out + self.shortcut_Conv_01(identity))
        identity  = out
        
        # Conv2d_Block_02
        out = F.relu(self.Bn_02(self.Conv_02(out)))
        out = self.Bn_02(self.Conv_03(out))
        out = F.relu(out + self.shortcut_Conv_02(identity))
        identity  = out

        out = F.relu(self.Bn_02(self.Conv_03(out)))
        out = self.Bn_02(self.Conv_03(out))
        out = F.relu(out + self.shortcut_Conv_03(identity))
        identity  = out

        # Conv2d_Block_03
        out = F.relu(self.Bn_03(self.Conv_04(out)))
        out = self.Bn_03(self.Conv_05(out))
        out = F.relu(out + self.shortcut_Conv_04(identity))
        identity  = out
        
        out = F.relu(self.Bn_03(self.Conv_05(out)))
        out = self.Bn_03(self.Conv_05(out))
        out = F.relu(out + self.shortcut_Conv_05(identity))
        identity  = out

        # Conv2d_Block_04
        out = F.relu(self.Bn_04(self.Conv_06(out)))
        out = self.Bn_04(self.Conv_07(out))
        out = F.relu(out + self.shortcut_Conv_06(identity))
        identity  = out
        
        out = F.relu(self.Bn_04(self.Conv_07(out)))
        out = self.Bn_04(self.Conv_07(out))
        out = F.relu(out + self.shortcut_Conv_07(identity))
        identity  = out
        
        out = F.avg_pool2d(out,4)
        out = out.view(out.size(0),-1)
        out = self.linear(out)

        return out


        # print(out_first.shape)

