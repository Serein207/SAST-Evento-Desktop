#include "evento_edit.h"
#include "evento_helper.h"
#include "evento_service.h"
#include "information_service.h"
#include "type_model.h"

EventoEditController* EventoEditController::getInstance() {
    static EventoEditController instance;
    return &instance;
}

EventoEditController* EventoEditController::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
    auto instance = getInstance();
    QJSEngine::setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}

void EventoEditController::preload() {
    InformationService::getInstance().load_EditInfo();
}

void EventoEditController::createEvento(const QString& title, const QString& description,
                                        const QString& eventStart, const QString& eventEnd,
                                        const QString& registerStart, const QString& registerEnd,
                                        int index, int locationId,
                                        const QVariantList& departmentIds, const QString& tag) {
    auto typeId = TypeModel::getInstance()->getID(index);
    if (property("isEditMode").toBool()) {
        EventoService::getInstance().edit(EventoHelper::getInstance()->property("id").toInt(),
                                          title, description, eventStart, eventEnd, registerStart,
                                          registerEnd, typeId, locationId, departmentIds, tag);
    } else {
        EventoService::getInstance().create(title, description, eventStart, eventEnd, registerStart,
                                            registerEnd, typeId, locationId, departmentIds, tag);
    }
}

void EventoEditController::update(const DTO_Evento& event) {
    QString departmentIds = u"["_qs;
    for (const auto& department : event.departments) {
        departmentIds += QString::number(department.id) + ",";
    }
    *(departmentIds.end() - 1) = u']';
    QMetaObject::invokeMethod(
        this,
        [&]() {
            setProperty("eventStart", event.gmtEventStart.toString("yyyy-MM-ddThh:mm:ss"));
            setProperty("eventEnd", event.gmtEventEnd.toString("yyyy-MM-ddThh:mm:ss"));
            setProperty("registerStart",
                        event.gmtRegistrationStart.toString("yyyy-MM-ddThh:mm:ss"));
            setProperty("registerEnd", event.gmtRegistrationEnd.toString("yyyy-MM-ddThh:mm:ss"));
            setProperty("departmentIds", departmentIds);
        },
        Qt::BlockingQueuedConnection);
}

void EventoEditController::loadEditInfo() {
    if (m_isEditMode)
        update(EventoService::getInstance().edit(EventoHelper::getInstance()->m_id));
    preload();
}
