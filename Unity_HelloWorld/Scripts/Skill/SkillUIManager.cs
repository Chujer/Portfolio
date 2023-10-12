using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkillUIManager : MonoBehaviour
{
    public GameObject selectSkill;
    public HotKeySkillSlot selectHotKeySlot;
    public Sprite lockImage;
    // Start is called before the first frame update
    void Start()
    {
        selectSkill = transform.Find("SelectSkill").gameObject;
    }

    void Update()
    {
        if(selectSkill.gameObject.activeSelf )
        {
            selectSkill.transform.position = Input.mousePosition;

        }

    }

    public void SetSelectSkill(SkillData skillData)
    {
        selectSkill.GetComponent<SkillData>().SetSkill(skillData.skillNum);
        if (selectSkill.GetComponent<SkillData>().skillNum != 0)
            selectSkill.gameObject.SetActive(true);
    }


    public void SetHotKeySkill()
    {
        if (selectSkill == null)
            return;
        selectHotKeySlot.SetSkillNum(selectSkill.GetComponent<SkillData>().skillNum);
        selectSkill.gameObject.SetActive(false);
    }

    public void SetHotKey(HotKeySkillSlot hotkey)
    {
        selectHotKeySlot = hotkey;
    }

    public void RemoveHotKey()
    {
        selectHotKeySlot = null;
    }
}
