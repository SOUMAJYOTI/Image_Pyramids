/* This code has been contributed by Joseph Pan <https://github.com/wzpan> 
/* in a modification of the earlier code which was actually a build up of 
/* the Gaussian pyramid

/** 
 * buildLaplacianPyramid    -   build a laplacian pyramid from a single image
 *
 * @param src   -   source image
 * @param dst   -   destination vector of maxlevel+1 image
 * @param maxlevel  -   max level
 */
void buildLaplacianPyramid(const cv::Mat &src, std::vector<cv::Mat> &dst, const int maxlevel)
{
    if (maxlevel < 2)
        return;

    // build gaussian pyramid
    std::vector<cv::Mat> gPyramid;
    cv::buildPyramid(src, gPyramid, maxlevel);
    std::vector<cv::Mat>::const_iterator it = gPyramid.begin();
    std::vector<cv::Mat>::const_iterator itend = gPyramid.end();

    // build laplacian pyramid
    cv::Mat upsample, current;

    while (it < itend - 1) {
        current = (*it++).clone();  // current level
        cv::pyrUp(*it, upsample);   // upsampling upper level
        dst.push_back(current - upsample);  // subtract the two
    }
    // top level
    dst.push_back(*it);
}

/** 
 * buildLaplacianPyramid    -   build a laplacian pyramid from a vector of images
 *
 * @param src   -   vector of source images
 * @param dst   -   destination vector of vectors of maxlevel+1 image
 * @param maxlevel  -   max level
 */
void buildLaplacianPyramid(const std::vector<cv::Mat> &src, std::vector<std::vector<cv::Mat> > &dst, const int maxlevel)
{
    std::vector<cv::Mat>::const_iterator it = src.begin();
    std::vector<cv::Mat>::const_iterator itend = src.end();

    std::vector<cv::Mat> lPyramid;
    buildLaplacianPyramid(*it, lPyramid, maxlevel);
    for (; it < itend; ++it) {
        dst.push_back(lPyramid);
    }
}
