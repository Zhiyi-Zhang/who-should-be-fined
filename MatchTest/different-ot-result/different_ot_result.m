function different_ot_result(name1,name2)
a = textread(name1,'','delimiter',',','emptyvalue',NaN);
b = textread(name2,'','delimiter',',','emptyvalue',NaN);

sz= size(a)
before = [0.5 0.67 0.75];
after = [0.33 0.67 1];
a = check(a,before,after);
b = check(b,before,after);
for i=1:sz(1)
    a(i,2) = 1-a(i,2);
    b(i,2) = 1-b(i,2);
    
    if a(i,2)<1e-16
        a(i,2) = 1e-16;
    end
    if b(i,2)<1e-16
        b(i,2) = 1e-16;
    end
end
a(:,2) = a(:,2) .* 100;
b(:,2) = b(:,2) .* 100;

figure
h1=axes;

%------------------------figure3(c)
%%输入数据
X1=[];
Y1=[];
X2=[];
Y2=[];

%%输入数据
%-----------------------
plot(a(:,1),a(:,2),'linewidth',5.0,'Color',[0.274509817361832 0.560784339904785 0.823529422283173])
hold on

plot(b(:,1),b(:,2),'linewidth',5.0,'Color',[0.4 0.4 0.4])
hold on

my_yticks = [1e-14 1e-12 1e-10 1e-8 1e-6 1e-4 1e-2 1 100];
my_ylabels = {'<10^{-14}','10^{-12}','10^{-10}','10^{-8}','10^{-6}','10^{-4}','10^{-2}','1','10^{2}'};

l = 1;
r = 9;
for i=2:9
    if a(1,2)>my_yticks(i)
        l = i-1;
        break;
    end
    if b(1,2)>my_yticks(i)
        l = i-1;
        break;
    end
end

for i=2:9
    j = 10-i;
    if a(3,2)<my_yticks(j)
        r = j+1;
        break;
    end
    if b(3,2)<my_yticks(j)
        r = j+1;
        break;
    end
end
my_yticks = my_yticks(l:r);
my_ylabels = my_ylabels(l:r);

xlabel('Size of Unique data', 'FontSize',20)
ylabel('Error rate (%)', 'FontSize',20)
xticks([0.33 0.67 1])
xticklabels({'1-2 OT','2-3 OT','3-4 OT'})
yticks(my_yticks)
yticklabels(my_ylabels)
set(gca, 'YScale', 'log')
set(gca,'FontSize',20);
set(gca,'box','off');
set(gca,'linewidth',1.5);
set(gcf,'color',[1 1 1])
legend('Location','northeast')
legend({'1 leaker out of 6 receivers','3 leakers out of 6 receivers'})
h2=legend;
set(h2,'box','off')

Position=h1.Position;
eff=-0.05;
annotation('arrow',[Position(1) Position(1)],[Position(2)+eff+0.05 Position(2)+Position(4)+eff+0.07],'linewidth',3);
annotation('arrow',[Position(1) Position(1)+Position(3)+0.01],[Position(2)+eff+0.05 Position(2)+eff+0.05],'linewidth',3);
hgexport(gcf,[name1,'_',name2,'.eps']);
end

function ret = check(input,before,after)
ret = input;
sz = size(input);
for i=1:sz(1)
    for j=1:3
        if input(i,1) == before(j)
            ret(i,1) = after(j);
        end
    end
end
end