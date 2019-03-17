#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <set>

using namespace std;

string const NUCLEOTIDES = "ATGC";

class SuffixArray
{
  private:
    int n;
    vector<bool> isSeq2;
    vector<int> pos;
    vector<int> lcp;
    vector<string> suffix;
    void sortSuffixArray(string sequence);
    void createLcpArray();
    bool isTwoSeqExist(int top, int bot);

  public:
    SuffixArray(string sequence);
    ~SuffixArray();
    pair<int, set<int>> getAllLcsPos();
    void printSuffixArray();
    vector<int> getMaxLcsLength();
};

bool comparePair(pair<int, string> p1, pair<int, string> p2)
{
    return (p1.second.compare(p2.second) < 0);
}

SuffixArray::SuffixArray(string sequence)
{
    this->n = sequence.length();

    sortSuffixArray(sequence);

    this->isSeq2 = vector<bool>(this->n, false);
    for (int i = 0; i < this->n; i++)
    {
        if (this->suffix[i].find_first_of('#') != string::npos)
        {
            this->isSeq2[i] = true;
        }
    }

    createLcpArray();
}

SuffixArray::~SuffixArray()
{
}

void SuffixArray::sortSuffixArray(string sequence)
{
    vector<pair<int, string>> pos_suffix;

    for (int i = 0; i < n; ++i)
    {
        pos_suffix.push_back(pair<int, string>(i, sequence.substr(i)));
    }

    sort(pos_suffix.begin(), pos_suffix.end(), comparePair);

    for (int i = 0; i < n; ++i)
    {
        this->pos.push_back(pos_suffix[i].first);
        this->suffix.push_back(pos_suffix[i].second);
    }
}

void SuffixArray::createLcpArray()
{
    this->lcp = vector<int>(this->n, 0);
    for (int i = 1; i < this->n; ++i)
    {
        int length = min(suffix[i - 1].length(), suffix[i].length());

        for (int j = 0; j < length; j++)
        {
            if (suffix[i - 1][j] != suffix[i][j])
            {
                break;
            }
            ++lcp[i];
        }
    }
}

bool SuffixArray::isTwoSeqExist(int top, int bot)
{
    int sum = 0;
    for (int i = top; i < bot; i++)
    {
        sum += isSeq2[i];
    }

    if (sum == 0 || sum == (bot - top))
    {
        return false;
    }
    else
    {
        return true;
    }
}

pair<int, set<int>> SuffixArray::getAllLcsPos()
{
    int max = 0;
    set<int> lscPos;

    for (int top = 0; top < this->n - 1; top++)
    {
        for (int bot = top + 1; bot < this->n + 1; bot++)
        {
            if (isTwoSeqExist(top, bot))
            {
                // cout << top << "\t" << bot - 1 << "\t";
                // for(int i = top; i < bot; i++)
                // {
                //     cout << isSeq2[i];
                // }
                // cout << "\n";

                int d = distance(
                    this->lcp.begin(),
                    min_element(this->lcp.begin() + top + 1, this->lcp.begin() + bot));
                int curMax = lcp[d];
                if (curMax > max)
                {
                    max = curMax;

                    lscPos.clear();
                    lscPos.insert(this->pos[bot - 1]);
                }
                else if (curMax == max)
                {
                    lscPos.insert(this->pos[bot - 1]);
                }
                break;
            }
        }
    }
    return pair<int, set<int>>(max, lscPos);
}

void SuffixArray::printSuffixArray()
{
    for (int i = 0; i < this->n; ++i)
    {
        cout << pos[i] << "\t" << lcp[i] << "\t" << isSeq2[i] << "\t" << suffix[i].substr(0, 20) << "\n";
    }
}

string getRandDna(int n, int param)
{
    srand(time(NULL) + param);
    string dna = "";

    for (int i = 0; i < n; ++i)
    {
        dna += NUCLEOTIDES[rand() % 4];
    }

    return dna;
}

int main()
{
    int n1, n2;
    cout << "Size of 1st DNA sequence: ";
    cin >> n1;

    cout << "Size of 2nd DNA sequence: ";
    cin >> n2;

    string dna1, dna2;

    dna1 = getRandDna(n1, 0);
    dna2 = getRandDna(n2, 1);

    cout << "1st DNA (" << n1 << "):\n\t" << dna1 << "\n";
    cout << "2nd DNA (" << n2 << "):\n\t" << dna2 << "\n";

    string str = (dna1 + "#" + dna2 + "$");
    SuffixArray sa = SuffixArray(str);

    sa.printSuffixArray();
    pair<int, set<int>> lscpos = sa.getAllLcsPos();

    cout << "Maximal Unique Matches:\n";
    cout << "Length = " << lscpos.first << "\n";
    for (set<int>::iterator it = lscpos.second.begin(); it != lscpos.second.end(); ++it)
    {
        int pos1, pos2;

        cout << str.substr(*it, lscpos.first) << ":\t" << *it << "\n";
    }
    cout << "\n";

    return 0;
}
