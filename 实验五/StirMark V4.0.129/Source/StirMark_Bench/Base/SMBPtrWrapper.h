#if !defined(_SMBPTRWRAPPER_H_)
#define      _SMBPTRWRAPPER_H_

template <class SMBObject>

class CSMBPtrWrapper
{
public:
  // Note that the destructor free the memory pointed to by
  // the pointer so a newly allocated object (using new only)
  // should be given to the constructor and should not be
  // destroyed.
  CSMBPtrWrapper(SMBObject* in_ptst = 0) : m_ptst(in_ptst) { };
  CSMBPtrWrapper(const CSMBPtrWrapper<SMBObject> &in_ptstwrp)
  {
    m_ptst = in_ptstwrp() ? in_ptstwrp()->Clone() : 0;
  };

  ~CSMBPtrWrapper() { delete m_ptst; }; // Delete the pointed object

  const SMBObject* operator() () const { return m_ptst; };
        SMBObject* operator() ()       { return m_ptst; };

private:
  CSMBPtrWrapper<SMBObject>& operator=(const CSMBPtrWrapper<SMBObject>& in_ptst)
  {
    delete m_ptst;
    m_ptst = in_ptst()->Clone();
    return *this;
  }

  SMBObject* m_ptst;
};


#endif // _SMBPTRWRAPPER_H_
