#ifndef SVGANIMATIONELEMENT_H
#define SVGANIMATIONELEMENT_H

#include "svgelementhead.h"

namespace lunasvg {

class SVGAnimationElement : public SVGElementHead
{
public:
    SVGAnimationElement(ElementID elementId, SVGDocument* document);
    bool setProperty(PropertyID, const std::string&);
    bool isSVGAnimationElement() const { return false; }
    bool isAnimationValid() const { return m_animationValid; }
    bool isAnimationInitialised() const { return m_animationInitialised; }
    void initialiseAnimation();
    void resetAnimation();
    void applyAnimation();
    SVGElementHead* targetElement() const { return m_targetElement; }
    virtual void calculateFromAndTo(const std::string& from, const std::string& to) =  0;
    virtual void calculateFromAndBy(const std::string& from, const std::string& by) =  0;
    virtual std::vector<float> calculateValuesAndDistances(const std::vector<std::string>& values) =  0;
    virtual void calculateAnimatedValue(float percent, unsigned int valueIndex, int repeatCount) =  0;

private:
    bool m_animationValid;
    bool m_animationInitialised;
    SVGElementHead* m_targetElement;
};

} // namespace lunasvg

#endif // SVGANIMATIONELEMENT_H
